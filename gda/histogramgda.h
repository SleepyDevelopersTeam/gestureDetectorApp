#ifndef HISTOGRAMGDA_H
#define HISTOGRAMGDA_H

#include "abstractgda.h"
#include "common/backgrounddetector.h"

class HistogramGDA: public AbstractGDA
{
	Q_OBJECT
	
public:
	HistogramGDA();
	~HistogramGDA();
	
protected:
	void onNextFrameConsumed(cv::Mat& nextFrame);
	
private:
	BackgroundDetector* bgDetector;
};

#endif // HISTOGRAMGDA_H
