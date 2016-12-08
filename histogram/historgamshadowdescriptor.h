#ifndef HISTORGAMSHADOWDESCRIPTOR_H
#define HISTORGAMSHADOWDESCRIPTOR_H

#include "histogram.h"
#include "opencv/cv.h"

class HistorgamShadowDescriptor
{
public:
	HistorgamShadowDescriptor(unsigned clusters);
	~HistorgamShadowDescriptor();
	
	bool closeEnough(HistorgamShadowDescriptor& hsd, float maxDifference);
	
	void createFrom(cv::Mat& mask, unsigned char threshold = 127);
	
private:
	Histogram* horz;
	Histogram* vert;
};

#endif // HISTORGAMSHADOWDESCRIPTOR_H
