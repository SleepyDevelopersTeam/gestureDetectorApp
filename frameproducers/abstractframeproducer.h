#ifndef ABSTRACTFRAMEPRODUCER_H
#define ABSTRACTFRAMEPRODUCER_H

#include <opencv/cv.h>

class AbstractFrameProducer
{
public:
	AbstractFrameProducer();
	~AbstractFrameProducer();
	
	/**
	 * @brief getFrameWidth
	 * @return width of the produced frames
	 */
	size_t getFrameWidth();
	/**
	 * @brief getFrameHeight
	 * @return height of the produced frames
	 */
	size_t getFrameHeight();
	
	/**
	 * @brief Launches some operation that will produce the frames. Blocking (?).
	 */
	virtual void startProducing() = 0;
	
protected:
	
	/**
	 * @brief Call this function every time a new video frame is produced.
	 * Emits FRAME_PRODUCED signal internally.
	 * @param frame - the newly produced frame
	 */
	void onFrameGenerated(cv::Mat& frame);
	
	cv::Mat lastFrame;
};

#endif // ABSTRACTFRAMEPRODUCER_H
