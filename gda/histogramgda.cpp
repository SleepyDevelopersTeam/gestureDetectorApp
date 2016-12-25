#include "histogramgda.h"
#include "descriptors/pose/histogramposedescriptor.h"
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>

const char* SHADOW_NAME = "HistogramGDA Output: Shadow";
const char* BACKGROUND_NAME = "HistogramGDA Output: Background";

HistogramGDA::HistogramGDA(unsigned int maxPoses)
{
	bgDetector = 0;
	histogramLength = 100;
	showShadow = showBackgroundMask = false;
	gesture = new KeyPoseGestureDescriptor(maxPoses);
}

void HistogramGDA::onNextFrameConsumed(cv::Mat &nextFrame)
{
	// TODO
	if (bgDetector == 0)
	{
		bgDetector = new BackgroundDetector(nextFrame.size().width, nextFrame.size().height);
	}
	cv::Mat grayscale = cv::Mat(nextFrame.rows, nextFrame.cols, CV_8UC1, cv::Scalar(0, 0, 0));
	// cv::Mat test = cv::Mat(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0, 0, 0));
	cv::cvtColor(nextFrame, grayscale, CV_BGR2GRAY, 1);
	cv::GaussianBlur(grayscale, grayscale, cv::Size(9,9), 3);
	bgDetector->accumulate(&grayscale);
	bgDetector->getForegroundMask(grayscale);

	if (showBackgroundMask)
		cv::imshow(BACKGROUND_NAME, grayscale);
	// bgDetector->getForegroundMask(test);
	// bd->getDisplayableDisp(test);

	preproducer.preproduce(grayscale);

	cv::Rect2i largestBlob = preproducer.findLargestBlob(grayscale);
	if (largestBlob.width > 0 && largestBlob.height > 0)
	{
		cv::Mat blob = grayscale(largestBlob);

		HistogramPoseDescriptor d(histogramLength);
		d.createFrom(blob);
		if (showShadow)
		{
			drawer.draw(blob, d);
			cv::imshow(SHADOW_NAME, drawer.canvas);
		}
	}
	// auto descriptor = HistogramShadowDescriptor::calculate(nextFrame, this->shadowDescriptorProps);
	// recentDecriptors.push(descriptor);
	// auto gesture = recentDescriptors.formGestureDecriptor();
	// GestureLibrary::getInstance()->matchGesture(
}

void HistogramGDA::enableOutput(bool showShadow, bool showBackgroundMask)
{
	this->showShadow = showShadow;
	this->showBackgroundMask = showBackgroundMask;

	if (showShadow) cv::namedWindow(SHADOW_NAME);
	else cv::destroyWindow(SHADOW_NAME);

	if (showBackgroundMask) cv::namedWindow(BACKGROUND_NAME);
	else cv::destroyWindow(BACKGROUND_NAME);
}

HistogramGDA::~HistogramGDA()
{
	delete bgDetector;
	if (showShadow) cv::destroyWindow(SHADOW_NAME);
	if (showBackgroundMask) cv::destroyWindow(BACKGROUND_NAME);
}
