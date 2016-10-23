#include "abstractframeproducer.h"

AbstractFrameProducer::AbstractFrameProducer()
{
}

size_t AbstractFrameProducer::getFrameWidth()
{
	return this->lastFrame.size().width;
}

size_t AbstractFrameProducer::getFrameHeight()
{
	return this->lastFrame.size().height;
}
