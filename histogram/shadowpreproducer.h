#ifndef SHADOWPREPRODUCER_H
#define SHADOWPREPRODUCER_H

#include <opencv/cv.h>

class ShadowPreproducer
{
public:
	ShadowPreproducer();

	void preproduce(cv::Mat& shadow);
	cv::Rect2i findLargestBlob(cv::Mat& shadow);

	float blobsProportion;
	float removedBlobsRelativeSize;
	int removedPixelsCount;

private:
	cv::Mat structElem;
	cv::Mat components;
};

#endif // SHADOWPREPRODUCER_H
