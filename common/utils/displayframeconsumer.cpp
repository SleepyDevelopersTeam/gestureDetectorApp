#include "displayframeconsumer.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include "histogram/historgamshadowdescriptor.h"

DisplayFrameConsumer::DisplayFrameConsumer(std::string wname)
{
	cvNamedWindow(wname.c_str());
	cvNamedWindow("Raw");
	cvNamedWindow("Test");
	windowName = wname;
	sp = ShadowPreproducer();
	bd = 0;
	drawer = HistogramDrawer(0.5F, 0.5F);
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
	cv::Mat test = cv::Mat(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0, 0, 0));
	cv::cvtColor(frame, grayscale, CV_BGR2GRAY, 1);
	cv::GaussianBlur(grayscale, grayscale, cv::Size(9,9), 3);
	bd->accumulate(&grayscale);
	bd->getForegroundMask(grayscale);
	bd->getForegroundMask(test);
	// bd->getDisplayableDisp(test);

	sp.preproduce(grayscale);

	cv::Rect2i largestBlob = sp.findLargestBlob(grayscale);
	if (largestBlob.width > 0 && largestBlob.height > 0)
	{
		cv::Mat blob = grayscale(largestBlob);
		cv::imshow("Raw", blob);

		HistorgamShadowDescriptor d(100);
		d.createFrom(blob);
		drawer.draw(blob, d);

		cv::imshow("Test", drawer.canvas);
	}

//	cv::Vec3b colors[] = {
//		cv::Vec3b(255, 0 ,0),
//		cv::Vec3b(255, 160, 0),
//		cv::Vec3b(160, 0, 160),
//		cv::Vec3b(0, 160, 255),
//		cv::Vec3b(0, 0, 255),
//		cv::Vec3b(0, 160, 0)
//	};
//	for(int r = 0; r < frame.rows; ++r)
//	{
//		for(int c = 0; c < frame.cols; ++c)
//		{
//			int label = sp.components.at<int>(r, c);
//			cv::Vec3b &pixel = frame.at<cv::Vec3b>(r, c);
//			pixel = colors[label % 6];
//		}
//	}
//	cv::imshow("Raw", frame);

	cv::imshow(windowName.c_str(), grayscale);
}

DisplayFrameConsumer::~DisplayFrameConsumer()
{
	if (bd != 0)
		delete bd;
}
