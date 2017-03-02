#include "histogramdrawer.h"

HistogramDrawer::HistogramDrawer(float horzAmount, float vertAmount)
{
	canvas.create(1, 1, CV_8U);
	horzHistAmount = horzAmount;
	vertHistAmount = vertAmount;
}

void HistogramDrawer::draw(cv::Mat &shadow, HistogramPoseDescriptor& descriptor)
{
	unsigned additionalWidth  = (unsigned) (shadow.cols * vertHistAmount);
	unsigned additionalHeight = (unsigned) (shadow.rows * horzHistAmount);
	unsigned hlen = descriptor.getHorizontal()->getLength();
	unsigned vlen = descriptor.getVertical()->getLength();
	unsigned cols = (unsigned) shadow.cols;
	unsigned rows = (unsigned) shadow.rows;
	unsigned imageWidth  = (cols >= hlen)? cols : hlen;
	unsigned imageHeight = (rows >= vlen)? rows : vlen;
	unsigned totalWidth  = additionalWidth  + imageWidth;
	unsigned totalHeight = additionalHeight + imageHeight;

	uchar black = 0;
	uchar white = 255;

	canvas.create(totalHeight, totalWidth, canvas.type());
	canvas.setTo(black);

	// drawing the shadow itself
	for (unsigned x = 0; x < cols; x++)
	{
		for (unsigned y = 0; y < rows; y++)
		{
			canvas.at<uchar>(y + additionalHeight, x) = shadow.at<uchar>(y, x);
		}
	}

	// assuming that both hists are normalized
	// drawing the horizontal hist
	float max = descriptor.getHorizontal()->max();
	for (unsigned x = 0; x < hlen; x++)
	{
		unsigned lim = (unsigned int) ((1 - descriptor.getHorizontal()->at(x) / max) * additionalHeight);
		for (unsigned y = 0; y < additionalHeight; y++)
		{
			canvas.at<uchar>(y, x) = ((y > lim)? white: black);
		}
	}

	// drawing the vertical hist
	max = descriptor.getVertical()->max();
	for (unsigned y = 0; y < vlen; y++)
	{
		unsigned lim = (unsigned int) (descriptor.getVertical()->at(y) / max * additionalWidth);
		for (unsigned x = 0; x < additionalWidth; x++)
		{
			canvas.at<uchar>(y + additionalHeight, x + imageWidth) = ((x <= lim)? white: black);
		}
	}
}
