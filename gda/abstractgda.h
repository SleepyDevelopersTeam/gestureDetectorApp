#ifndef ABSTRACTGDA_H
#define ABSTRACTGDA_H

#include <opencv/cv.h>
#include <QObject>
#include "frameproducers/abstractframeproducer.h"
#include "descriptors/gesture/abstractgesturedescriptor.h"

/**
 * @brief The Abstract Gesture Detector Algorithm class
 */
class AbstractGDA: public QObject
{
	Q_OBJECT

public:
	AbstractGDA();
	~AbstractGDA();

	/**
	 * @brief Links the algorithm to a source of video frames to consume. GDA is not responsible for freeing it.
	 * When linked, consumes every produced frame (see onNextFrameConsumed).
	 * @param producer - the source of video frames
	 */
	void consume(AbstractFrameProducer& producer);

	/**
	 * @brief Stops consuming frames from FrameProducer and disconnects from it.
	 * Method does not free the FrameProducer, but nulls link for it.
	 */
	void stopConsuming();

	/**
	 * @brief Returns calculated value of the GDA fitness to processed data.
	 * Return values are to be in [0..1] range, where 1 means perfect GDA work
	 * and 0 means inapplicability.
	 * This mechanism is used inside AdaptiveGDA.
	 * @return The fitness in range of [0..1] or a negative value if fitness cannot be calculated now.
	 */
	double getFitness();

signals:
	void gestureDetected(int gestureId);

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

	/**
	 * @brief Variable is used to compare gesture candidates with gesture models in library
	 */
	double matchingAccuracy;

	/**
	 * @brief Variable is used to store fitness of this algorithm in application to data
	 * it obtains from frameProducer. You should store here a value in range of [0..1].
	 * Value can be calculated either of last frame or of last N frames, but it should
	 * represent quite actual fitness.
	 * If value cannot be obtained at a particular moment, place any negative value here.
	 */
	double alorithmFitness;

private slots:
	void frameProduced(cv::Mat& frame);

private:
	AbstractFrameProducer* frameProducer;
};

#endif // ABSTRACTGDA_H
