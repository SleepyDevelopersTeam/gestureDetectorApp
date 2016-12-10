#include "displayframeconsumer.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <QDebug>

DisplayFrameConsumer::DisplayFrameConsumer(std::string wname)
{
	cvNamedWindow(wname.c_str());
	cvNamedWindow("Raw");
	cvNamedWindow("Test");
	windowName = wname;
	sp = ShadowPreproducer();
	bd = 0;
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
		cv::imshow("Raw", grayscale(largestBlob));
	
	cv::imshow(windowName.c_str(), grayscale);
	cv::imshow("Test", test);
}

DisplayFrameConsumer::~DisplayFrameConsumer()
{
	if (bd != 0)
		delete bd;
}
