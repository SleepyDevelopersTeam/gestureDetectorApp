#include "histogramposedescriptor.h"
#include <QDebug>

HistogramPoseDescriptor::HistogramPoseDescriptor(unsigned clusters)
{
	horz = new Histogram(clusters);
	vert = new Histogram(clusters);
	len = clusters;
}
HistogramPoseDescriptor::~HistogramPoseDescriptor()
{
	delete horz;
	delete vert;
}

bool HistogramPoseDescriptor::similarTo(AbstractPoseDescriptor &hsd, double maxDifference)
{
	// TODO
//	float x = horz->difference(*(hsd.horz));
//	float y = vert->difference(*(hsd.vert));
//	return (x*x + y*y) < maxDifference * maxDifference;
	return false;
}

void HistogramPoseDescriptor::createFrom(cv::Mat &mask, uchar threshold)
{
	unsigned width = mask.cols;
	unsigned height = mask.rows;

	Histogram h(width);
	Histogram v(height);

	// each pixel
	for (unsigned y = 0; y < height; ++y)
	{
		for (unsigned x = 0; x < width; ++x)
		{
			uchar val = mask.at<uchar>(y, x);
			if (val > threshold)
			{
//				unsigned horzIndex = x * len / width;
//				unsigned vertIndex = y * len / height;
//				horz->at(horzIndex) += 1.0F;
//				vert->at(vertIndex) += 1.0F;
				h[x] += 1.0F;
				v[y] += 1.0F;
			}
		}
	}
	horz->scaledFrom(h);
	vert->scaledFrom(v);
	horz->normalize();
	vert->normalize();
}

Histogram* HistogramPoseDescriptor::getHorizontal() { return horz; }
Histogram* HistogramPoseDescriptor::getVertical() { return vert; }


