#include "displayframeconsumer.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <QDebug>

DisplayFrameConsumer::DisplayFrameConsumer(std::string wname)
{
	cvNamedWindow(wname.c_str());
	windowName = wname;
	sp = ShadowPreproducer();
}

void DisplayFrameConsumer::consume(AbstractFrameProducer &producer)
{
	connect(&producer, SIGNAL(frameProduced(cv::Mat&)), this, SLOT(consumeFrame(cv::Mat&)));
}

void DisplayFrameConsumer::consumeFrame(cv::Mat &frame)
{
	if (bd == 0)
	{
		bd = new BackgroundDetector(frame.cols, frame.rows);
	}
	cv::Mat grayscale = cv::Mat(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0, 0, 0));
	cv::cvtColor(frame, grayscale, CV_BGR2GRAY, 1);
	bd->accumulate(&grayscale);
	// bd->getForegroundMask(grayscale);
	// sp.preproduce(frame);
	cv::imshow(windowName.c_str(), grayscale);
}

DisplayFrameConsumer::~DisplayFrameConsumer()
{
	if (bd != 0)
		delete bd;
}
