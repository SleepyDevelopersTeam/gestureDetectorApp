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
	
	/**
	 * @brief Links the algorithm to a source of video frames to consume. GDA is not responsible for freeing it.
	 * When linked, consumes every produced frame (see onNextFrameConsumed).
	 * @param producer - the source of video frames
	 */
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
	
	/**
	 * @brief Call this method every time you obtained a gesture descriptor.
	 * It will call internally GestureLibrary::match to chech if the candidate
	 * is a predefined gesture. If a match found, it will emit signal
	 * GESTURE_DETECTED internally.
	 * @param candidate - the obtained descriptor that can be a predefined gesture.
	 */
	void onGestureCandidate(AbstractGestureDescriptor& candidate);
	
	double matchingAccuracy;
	
private:
	AbstractFrameProducer* frameProducer;
};

#endif // ABSTRACTGDA_H
