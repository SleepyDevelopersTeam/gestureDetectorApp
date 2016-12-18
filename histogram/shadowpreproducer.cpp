#include "shadowpreproducer.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QDebug>
// #include "highgui.h"
//#include <stdlib.h>
//#include <stdio.h>

using namespace cv;

ShadowPreproducer::ShadowPreproducer()
{
	structElem = getStructuringElement(MORPH_RECT, Size(10, 10), Point(1, 1));
	components = cv::Mat(1, 1, CV_32S);
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

cv::Rect2i ShadowPreproducer::findLargestBlob(cv::Mat &shadow)
{
	components.create(shadow.size().width, shadow.size().height, components.type());
	int ncomp = cv::connectedComponents(shadow, components, 4);
	if (ncomp == 1)
		return cv::Rect2i(0, 0, 0, 0);

	unsigned int* areas = new unsigned int [ncomp];
	// min and max coords for blobs: [i] = { min_x, min_y, max_x, max_y }
	unsigned short* corners = new unsigned short [ncomp * 4];
	for (int i = 0; i < ncomp; i++)
	{
		areas[i] = 0;
		corners[4*i+0] = corners[4*i+1] = 32666;
		corners[4*i+2] = corners[4*i+3] = 0;
	}

	for(unsigned short r = 0; r < components.rows; ++r)
	{
		for(unsigned short c = 0; c < components.cols; ++c)
		{
			int label = components.at<int>(r, c);
			areas[label]++;

			if (c < corners[label*4 + 0]) // min_x
				corners[label*4 + 0] = c;

			if (r < corners[label*4 + 1]) // min_y
				corners[label*4 + 1] = r;

			if (c > corners[label*4 + 2]) // max_x
				corners[label*4 + 2] = c;

			if (r > corners[label*4 + 3]) // max_y
				corners[label*4 + 3] = r;
		 }
	}

	// finding max area
	// remember: 0 is for background area
	unsigned int max = 1;
	for (int i = 2; i < ncomp; i++)
	{
		if (areas[i] > areas[max])
			max = i;
	}
	if (areas[max] == 0)
		return cv::Rect2i(0, 0, 0, 0);

	int x = corners[max*4 + 0];
	int y = corners[max*4 + 1];
	int width  = ((int) corners[max*4 + 2]) - x + 1;
	int height = ((int) corners[max*4 + 3]) - y + 1;
	if (width < 0) width = 0;
	if (height < 0) height = 0;

	delete[] areas;
	delete[] corners;

	return cv::Rect2i(x, y, width, height);
}
