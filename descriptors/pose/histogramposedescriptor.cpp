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
	HistogramPoseDescriptor* another = dynamic_cast <HistogramPoseDescriptor*> (&hsd);
	if (another == 0)
	{
		// different types => different descriptors
		return false;
	}
	float x = horz->difference(*(another->horz));
	float y = vert->difference(*(another->vert));
	return (x*x + y*y) < maxDifference * maxDifference;
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

void HistogramPoseDescriptor::write(std::ostream &to)
{
	to << "Test" << std::endl;
	to << (int) 77;
}

std::vector<float>* HistogramPoseDescriptor::getFeaturesVector()
{
	std::vector<float>* v = new std::vector<float>();
	v->push_back(1.30F);
	v->push_back(2.00F);
	v->push_back(3.05F);
	return v;
}


