#include "histogramgda.h"
#include <opencv/cv.h>

HistogramGDA::HistogramGDA()
{
	bgDetector = 0;
}

void HistogramGDA::onNextFrameConsumed(cv::Mat &nextFrame)
{
	// TODO
	if (bgDetector == 0)
	{
		bgDetector = new BackgroundDetector(nextFrame.size().width, nextFrame.size().height);
	}
	bgDetector->accumulate(&nextFrame);
	// auto descriptor = HistogramShadowDescriptor::calculate(nextFrame, this->shadowDescriptorProps);
	// recentDecriptors.push(descriptor);
	// auto gesture = recentDescriptors.formGestureDecriptor();
	// GestureLibrary::getInstance()->matchGesture(
}

HistogramGDA::~HistogramGDA()
{
	delete bgDetector;
}
