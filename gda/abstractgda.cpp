#include "abstractgda.h"
#include "common/gesturelibrary.h"

AbstractGDA::AbstractGDA()
{
	this->frameProducer = 0;
	this->matchingAccuracy = 0.1; // TODO: override this default value
	this->alorithmFitness = -1.0;
}

void AbstractGDA::consume(AbstractFrameProducer& producer)
{
	this->frameProducer = &producer;
	connect(frameProducer, SIGNAL(frameProduced(cv::Mat&)), this, SLOT(frameProduced(cv::Mat&)));
}

void AbstractGDA::frameProduced(cv::Mat &frame)
{
	onNextFrameConsumed(frame);
}

void AbstractGDA::stopConsuming()
{
	disconnect(frameProducer, SIGNAL(frameProduced(cv::Mat&)), this, SLOT(frameProduced(cv::Mat&)));
	this->frameProducer = 0;
}

void AbstractGDA::onGestureCandidate(AbstractGestureDescriptor &candidate)
{
	int detected = GestureLibrary::matchGesture(candidate);
	if (detected != -1)
	{
		this->onGestureDetected(detected);
	}
}

void AbstractGDA::onGestureDetected(int gestureId)
{
	emit gestureDetected(gestureId);
}

double AbstractGDA::getFitness()
{
	return this->alorithmFitness;
}

AbstractGDA::~AbstractGDA()
{
	
}
