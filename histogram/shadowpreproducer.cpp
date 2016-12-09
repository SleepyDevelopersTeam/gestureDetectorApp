#include "shadowpreproducer.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
// #include "highgui.h"
//#include <stdlib.h>
//#include <stdio.h>

using namespace cv;

ShadowPreproducer::ShadowPreproducer()
{
	structElem = getStructuringElement(MORPH_RECT, Size(5, 5), Point(1, 1));
}

void ShadowPreproducer::preproduce(cv::Mat &shadow)
{
	cv::Mat temp;
	shadow.copyTo(temp);
	erode(shadow, temp, structElem);
	dilate(temp, shadow, structElem);
	dilate(temp, shadow, structElem);
	erode(shadow, temp, structElem);
}

cv::Rect2i& ShadowPreproducer::findLargestBlob(cv::Mat &shadow)
{
	
}
