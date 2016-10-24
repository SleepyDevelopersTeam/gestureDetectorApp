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
	// TODO: subscribe to a signal here
}

void AbstractGDA::stopConsuming()
{
	// TODO: unsubscribe from a signal here
	this->frameProducer = 0;
}

void AbstractGDA::onGestureCandidate(AbstractGestureDescriptor &candidate)
{
	int detected = GestureLibrary::matchGesture(candidate, this->matchingAccuracy);
	if (detected != -1)
	{
		this->onGestureDetected(detected);
	}
}

void AbstractGDA::onGestureDetected(int gestureId)
{
	// TODO: emit a signal here
}

double AbstractGDA::getFitness()
{
	return this->alorithmFitness;
}
