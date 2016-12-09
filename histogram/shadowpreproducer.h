#ifndef SHADOWPREPRODUCER_H
#define SHADOWPREPRODUCER_H

#include <opencv/cv.h>

class ShadowPreproducer
{
public:
	ShadowPreproducer();
	
	void preproduce(cv::Mat& shadow);
	cv::Rect2i& findLargestBlob(cv::Mat& shadow);
	
private:
	cv::Mat structElem;
};

#endif // SHADOWPREPRODUCER_H
