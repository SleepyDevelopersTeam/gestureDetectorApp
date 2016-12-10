#ifndef WEBCAMERAFRAMEPRODUCER_H
#define WEBCAMERAFRAMEPRODUCER_H

#include "abstractframeproducer.h"
// #include <opencv/cv.h>
#include <opencv/highgui.h>

class WebCameraFrameProducer : public AbstractFrameProducer
{
	Q_OBJECT
	
public:
	WebCameraFrameProducer();
	~WebCameraFrameProducer();
	
	void startProducing();
	
private:
	CvCapture* webcam;
	IplImage* lastFrameIpl;
};

#endif // WEBCAMERAFRAMEPRODUCER_H
