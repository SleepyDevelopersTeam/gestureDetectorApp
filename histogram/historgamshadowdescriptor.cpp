#include "historgamshadowdescriptor.h"

HistorgamShadowDescriptor::HistorgamShadowDescriptor(unsigned clusters)
{
	horz = new Histogram(clusters);
	vert = new Histogram(clusters);
}
HistorgamShadowDescriptor::~HistorgamShadowDescriptor()
{
	delete horz;
	delete vert;
}

bool HistorgamShadowDescriptor::closeEnough(HistorgamShadowDescriptor &hsd, float maxDifference)
{
	// TODO: normalize here (just before comparing) and scale hists to have the same widths
	float x = horz->difference(*(hsd.horz));
	float y = vert->difference(*(hsd.vert));
	return (x*x + y*y) < maxDifference * maxDifference;
}

void HistorgamShadowDescriptor::createFrom(cv::Mat &mask, uchar threshold)
{
	unsigned size = horz->getLength();
	unsigned width = mask.cols;
	unsigned height = mask.rows;
	// each pixel
	for (unsigned y = 0; y < height; ++y)
	{
		for (unsigned x = 0; x < width; ++x)
		{
			uchar val = mask.at<uchar>(y, x);
			if (val > threshold)
			{
				unsigned horzIndex = x * size / width;
				unsigned vertIndex = y * size / height;
				horz->at(horzIndex) += 1.0F;
				vert->at(vertIndex) += 1.0F;
			}
		}
	}
	horz->normalize();
	vert->normalize();
}

Histogram* HistorgamShadowDescriptor::getHorizontal() { return horz; }
Histogram* HistorgamShadowDescriptor::getVertical() { return vert; }
