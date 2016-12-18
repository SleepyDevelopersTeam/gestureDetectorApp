#ifndef HISTOGRAMGDA_H
#define HISTOGRAMGDA_H

#include "abstractgda.h"
#include "common/backgrounddetector.h"
#include "histogram/shadowpreproducer.h"
#include "histogram/histogramdrawer.h"

class HistogramGDA: public AbstractGDA
{
	Q_OBJECT

public:
	HistogramGDA();
	~HistogramGDA();

	void enableOutput(bool showShadow, bool showBackgroundMask);

protected:
	void onNextFrameConsumed(cv::Mat& nextFrame);

private:
	BackgroundDetector* bgDetector;
	ShadowPreproducer preproducer;
	HistogramDrawer drawer;

	unsigned int histogramLength;
	bool showShadow;
	bool showBackgroundMask;
};

#endif // HISTOGRAMGDA_H
