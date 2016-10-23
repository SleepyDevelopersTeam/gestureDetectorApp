#ifndef ABSTRACTFRAMEPRODUCER_H
#define ABSTRACTFRAMEPRODUCER_H

#include <opencv/cv.h>

class AbstractFrameProducer
{
public:
	AbstractFrameProducer();
	~AbstractFrameProducer();
	
	size_t getFrameWidth();
	size_t getFrameHeight();
	
	virtual void startProducing() = 0;
	
protected:
	void onFrameGenerated(cv::Mat& frame);
	
private:
	cv::Mat lastFrame;
};

#endif // ABSTRACTFRAMEPRODUCER_H
