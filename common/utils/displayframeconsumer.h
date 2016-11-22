#ifndef DISPLAYFRAMECONSUMER_H
#define DISPLAYFRAMECONSUMER_H

#include <QObject>
#include <opencv/cv.h>
#include "frameproducers/abstractframeproducer.h"

class DisplayFrameConsumer: public QObject
{
	Q_OBJECT
public:
	DisplayFrameConsumer(std::string wname);
	
	void consume(AbstractFrameProducer& producer);
	
public slots:
	void consumeFrame(cv::Mat& frame);
	
private:
	std::string windowName;
};

#endif // DISPLAYFRAMECONSUMER_H
