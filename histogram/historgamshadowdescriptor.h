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

	Histogram* getHorizontal();
	Histogram* getVertical();
	
private:
	Histogram* horz;
	Histogram* vert;
	unsigned len;
};

#endif // HISTORGAMSHADOWDESCRIPTOR_H
