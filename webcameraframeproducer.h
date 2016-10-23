#ifndef WEBCAMERAFRAMEPRODUCER_H
#define WEBCAMERAFRAMEPRODUCER_H

#include "abstractframeproducer.h"

class WebCameraFrameProducer : public AbstractFrameProducer
{
public:
	WebCameraFrameProducer();
	~WebCameraFrameProducer();
	
	void startProducing();
};

#endif // WEBCAMERAFRAMEPRODUCER_H
