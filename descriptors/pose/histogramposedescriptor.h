#ifndef HISTOGRAMPOSEDESCRIPTOR_H
#define HISTOGRAMPOSEDESCRIPTOR_H

#include "abstractposedescriptor.h"
#include "histogram/histogram.h"
#include "opencv/cv.h"

class HistogramPoseDescriptor: public AbstractPoseDescriptor
{
public:
	HistogramPoseDescriptor(unsigned clusters);
	~HistogramPoseDescriptor();

	bool similarTo(AbstractPoseDescriptor &anotherDescriptor, double accuracy);

	void createFrom(cv::Mat& mask, unsigned char threshold = 127);

	Histogram* getHorizontal();
	Histogram* getVertical();

private:
	Histogram* horz;
	Histogram* vert;
	unsigned len;
};

#endif // HISTOGRAMPOSEDESCRIPTOR_H
