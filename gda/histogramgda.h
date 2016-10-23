#ifndef HISTOGRAMGDA_H
#define HISTOGRAMGDA_H

#include "abstractgda.h"

class HistogramGDA: public AbstractGDA
{
public:
	HistogramGDA();
	~HistogramGDA();
	
	void onNextFrameConsumed(cv::Mat& nextFrame);
};

#endif // HISTOGRAMGDA_H
