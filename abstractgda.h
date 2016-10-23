#ifndef ABSTRACTGDA_H
#define ABSTRACTGDA_H

#include <opencv/cv.h>
#include "abstractframeproducer.h"
#include "abstractgesturedescriptor.h"

/**
 * @brief The Abstract Gesture Detector Algorithm class
 */
class AbstractGDA
{
public:
	AbstractGDA();
	~AbstractGDA();
	
	void consume(AbstractFrameProducer& producer);
	
protected:
	virtual void onNextFrameConsumed(cv::Mat& nextFrame) = 0;
	void onGestureDetected(int gestureId);
	void onGestureCandidate(AbstractGestureDescriptor& candidate);
	
private:
	AbstractFrameProducer* frameProducer;
};

#endif // ABSTRACTGDA_H
