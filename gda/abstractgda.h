#ifndef ABSTRACTGDA_H
#define ABSTRACTGDA_H

#include <opencv/cv.h>
#include "frameproducers/abstractframeproducer.h"
#include "descriptors/abstractgesturedescriptor.h"

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
	/**
	 * @brief Implement your main algorithm logic inside this method.
	 * It is invoked every time when new video frame is consumed
	 * @param nextFrame - the video frame content itself
	 */
	virtual void onNextFrameConsumed(cv::Mat& nextFrame) = 0;
	
	/**
	 * @brief This method is called when a particular gesture is detected.
	 * It emits the GESTURE_DETECTED signal.
	 * @param gestureId - the id of the gesture in the library
	 */
	void onGestureDetected(int gestureId);
	void onGestureCandidate(AbstractGestureDescriptor& candidate);
	
private:
	AbstractFrameProducer* frameProducer;
};

#endif // ABSTRACTGDA_H
