#ifndef DISPLAYFRAMECONSUMER_H
#define DISPLAYFRAMECONSUMER_H

#include <QObject>
#include <opencv/cv.h>
#include "frameproducers/abstractframeproducer.h"

// TODO: temporary functionality to debug preproducing
#include "histogram/shadowpreproducer.h"
#include "common/backgrounddetector.h"
#include "histogram/histogramdrawer.h"

class DisplayFrameConsumer: public QObject
{
	Q_OBJECT
public:
	DisplayFrameConsumer(std::string wname);
	~DisplayFrameConsumer();

	void consume(AbstractFrameProducer& producer);

public slots:
	void consumeFrame(cv::Mat& frame);

private:
	std::string windowName;
	ShadowPreproducer sp;
	BackgroundDetector* bd;
	HistogramDrawer drawer;
};

#endif // DISPLAYFRAMECONSUMER_H
