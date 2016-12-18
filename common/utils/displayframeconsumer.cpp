#include "displayframeconsumer.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include "histogram/historgamshadowdescriptor.h"

DisplayFrameConsumer::DisplayFrameConsumer(std::string wname)
{
	cvNamedWindow(wname.c_str());
	windowName = wname;
}

void DisplayFrameConsumer::consume(AbstractFrameProducer &producer)
{
	connect(&producer, SIGNAL(frameProduced(cv::Mat&)), this, SLOT(consumeFrame(cv::Mat&)));
}

void DisplayFrameConsumer::consumeFrame(cv::Mat &frame)
{
	cv::imshow(windowName, frame);
}

DisplayFrameConsumer::~DisplayFrameConsumer()
{
	cv::destroyWindow(windowName);
}
