#include "histogramdrawer.h"

HistogramDrawer::HistogramDrawer()
{
	canvas.create(1, 1, CV_8U);
}

void HistogramDrawer::draw(cv::Mat &shadow, HistorgamShadowDescriptor &descriptor)
{
	unsigned additionalWidth = (unsigned) (shadow.cols * vertHistAmount);
	unsigned additionalHeight = (unsigned) (shadow.rows * horzHistAmount);
	unsigned totalWidth  = additionalWidth + shadow.cols;
	unsigned totalHeight = additionalHeight + shadow.rows;
	canvas.create(totalHeight, totalWidth, canvas.type());

	// drawing the shadow itself
	for (unsigned x = 0; x < shadow.cols; x++)
	{
		for (unsigned y = 0; y < shadow.rows; y++)
		{
			canvas.at<uchar>(y + additionalHeight, x) = shadow.at<uchar>(y, x);
		}
	}

	// drawing the horizontal hist
	unsigned hlen = descriptor.getHorizontal()->getLength();
	for (unsigned x = 0; x < descriptor.getHorizontal()->getLength(); x++)
	{
		// TODO
	}
}
