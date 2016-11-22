#include "lncframeproducer.h"
#include <QDebug>
#include <QDataStream>
#include <QNetworkInterface>
#include <QCoreApplication>
#include <QThread>
#include <iostream>
#include <opencv/cv.h>

const int imageFormat = CV_8UC3;

LNCFrameProducer::LNCFrameProducer()
{
	myServer = new QTcpServer(this);
	connect(myServer, SIGNAL(newConnection()), this, SLOT(newConnectionUser()));
	length  = -1;
	command = -1;
	width   = -1;
	height  = -1;
	port = 9091;
	
	lastFrame = cv::Mat(20, 20, imageFormat, cv::Scalar(255, 0, 0));
}

bool LNCFrameProducer::changePort(int port)
{
	if (myServer->isListening()) return false;
	this->port = port;
	return true;
}

void LNCFrameProducer::startProducing()
{
	startServer();
}

void LNCFrameProducer::createImageAndNotify()
{
	if ((size_t) width != getFrameWidth() || (size_t) height != getFrameHeight())
	{
		// size changed, need to recreate the image
		lastFrame.create(height, width, imageFormat);
	}
	decodeImage();
	onFrameGenerated(lastFrame);
}

void LNCFrameProducer::decodeImage()
{
	int frameSize = width * height;
	int ii = 0;
	int ij = 0;
	int di = +1;
	int dj = +1;

	for (int i = 0, ci = ii; i < height; ++i, ci += di) {
		for (int j = 0, cj = ij; j < width; ++j, cj += dj) {
			int y = (0xff & ((int) data[ci * width + cj]));
			int v = (0xff & ((int) data[frameSize + (ci >> 1) * width + (cj & ~1) + 0]));
			int u = (0xff & ((int) data[frameSize + (ci >> 1) * width + (cj & ~1) + 1]));
			y = y < 16 ? 16 : y;

			int r = (int) (1.164f * (y - 16) + 1.596f * (v - 128));
			int g = (int) (1.164f * (y - 16) - 0.813f * (v - 128) - 0.391f * (u - 128));
			int b = (int) (1.164f * (y - 16) + 2.018f * (u - 128));

			r = r < 0 ? 0 : (r > 255 ? 255 : r);
			g = g < 0 ? 0 : (g > 255 ? 255 : g);
			b = b < 0 ? 0 : (b > 255 ? 255 : b);

			lastFrame.at<cv::Vec3b>(i,j)[0]=r;
			lastFrame.at<cv::Vec3b>(i,j)[1]=g;
			lastFrame.at<cv::Vec3b>(i,j)[2]=b;
		}
	}
}

void LNCFrameProducer::findLocalAddress()
{
	// HACK for finding server address in local network
	foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
		{
		 //   qDebug() << address.toString();
			adr = address.toString();
		}
		if(adr[0]=='1' && adr[1]=='9' && adr[2]=='2')
			break;
	}
}

LNCFrameProducer::~LNCFrameProducer()
{
	stopServer();
	delete myServer;
}

void LNCFrameProducer::startServer()
{
	findLocalAddress();
	if(myServer->listen(QHostAddress(adr), port))
	{
		// QString text=QTime::currentTime().toString()+">>"+"server started in "+ myServer->serverAddress().toString()+"; port: "+ QString::number(myServer->serverPort());
		std::cout << "Server started succesfully at " << adr.toStdString() << ":" << port << std::endl;
	}
	else
	{
		std::cout << "Cannot start server on " << adr.toStdString() << ":" << port << std::endl;
		std::cout << "May be this port is already in use" << std::endl;
	}
}

void LNCFrameProducer::stopServer()
{
	myServer->close();
	camera->deleteLater();
	std::cout << "Server stopped" << std::endl;
	QCoreApplication::instance()->exit(0);
}

void LNCFrameProducer::newConnectionUser()
{
	camera = myServer->nextPendingConnection();
	connect(camera, SIGNAL(readyRead()), this, SLOT(readMsg()));
	connect(camera, SIGNAL(disconnected()), this, SLOT(disconnectUser()));
}

void LNCFrameProducer::disconnectUser()
{
	if (camera)
	{
		camera->deleteLater();
	}
}

void LNCFrameProducer::readMsg()
{
	if (!read(command)) {
		std::cout << "Error while reading command! Ignoring..." << std::endl;
	}

	// traces commands
//	qDebug() << "Cmd " << (int)command;
//	temp++;
//	if (temp > 10) stopServer();
	
	// SDTUDTP3Km
	// see https://github.com/SleepyDevelopersTeam/AndroidVideoStreamer/blob/master/README.md
	switch(command)
	{
		case HELLO_SERVER:
		{
			sendMsg(HELLO_CLIENT);
			qDebug() << "Client has connected";
			command = -1;
			break;
		}
		case GB_SERVER:
		{
			sendMsg(GB_CLIENT);
			qDebug() << "Client is disconnecting";
			command = -1;
			stopServer();
			// and after this restarting it to wait for a new connection, eternally
			startServer();
			break;
		}
		case LENGTH_CHANGE:
		{
			if (!read(length)) return;
			qDebug() << "Length changed to " << length;
			sendMsg(COMAND_EXECUTED);
			command = -1;
			break;
		}
		case FONE_RESET:
		{
			// TODO
			sendMsg(COMAND_EXECUTED);
			command = -1;
			break;
		}
		case ERROR:
		{
			// catch
			std::cout << "Communication error: situation 0x66" << std::endl;
			stopServer();
			command = -1;
			break;
		}
		case DATA:
		{
			data.clear();
			
			if (!read(width)) return;
			if (!read(height)) return;
			
			if (camera->bytesAvailable() < length) return;
			
			QByteArray arr = camera->readAll();
			for (int i = 0; i < arr.length(); ++i)
			{
				data.push_back(arr[i]);
			}
			sendMsg(DATA_RECEIVED);
			
			createImageAndNotify();
			
			command = -1;
			width = -1;
			height = -1;
			break;
		}
   }
}

bool LNCFrameProducer::read(char &var)
{
	QDataStream in(camera);
	if(var == -1)
	{
		if (camera->bytesAvailable() < (int) sizeof(char))
			return false;
		qint8 tmp;
		in >> tmp;
		var = (char) tmp;
	}
	return true;
}

bool LNCFrameProducer::read(short &var)
{
	QDataStream in(camera);
	if(var == -1)
	{
		if (camera->bytesAvailable() < (int)sizeof(short))
			return false;
		qint16 tmp;
		in>>tmp;
		var=(short)tmp;
	}
	return true;
}

bool LNCFrameProducer::read(int &var)
{
	QDataStream in(camera);
	if (var == -1)
	{
		if (camera->bytesAvailable() < (int)sizeof(int))
			return false;
		in>>var;
	}
	return true;
}

void LNCFrameProducer::sendMsg(COMMAND cmd)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out << (quint8) cmd;
	camera->write(msg);
}
