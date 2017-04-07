#include <QCoreApplication>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "frameproducers/webcameraframeproducer.h"
#include "common/utils/displayframeconsumer.h"
#include "gda/histogramgda.h"
#include "common/utils/descriptorwriter.h"
#include "descriptors/pose/allinoneposedescriptor.h"

AllInOnePoseDescriptor* acc = new AllInOnePoseDescriptor();
AbstractPoseDescriptor* createDescriptor(cv::Mat& nextFrame)
{
	acc->accumulateNext(nextFrame);
	if (acc->featuresCount() > 0)
		return acc;
	else
		return NULL;
}

int main(int argc, char *argv[])
{
	/*
	 * Typical main will be like this:
	 *
	 * auto fproducer = NetFrameProducer(9090);
	 *
	 * auto algorithm = AdaptiveGDA(new AbstractGDA[] {
	 *		new SkinColorGDA(),
	 *		new HistogramGDA(),
	 *		new BlackMagicGDA()
	 * });
	 *
	 * auto gestureListener = ConsoleLogGL(std::out);
	 *
	 * int exitCode = 0; bool repeatCloseGestureTwice = true;
	 * auto closeListener = AppCloseGestureListener(exitCode, repeatCloseGestureTwice);
	 *
	 * algorithm.consume(fproducer);
	 * gestureListener.listen(algorithm);
	 * closeListener.listen(algorithm);
	 *
	 * return fproducer.startProducing();
	 */

	QCoreApplication a(argc, argv);
	WebCameraFrameProducer fproducer;

	DisplayFrameConsumer displayer("Obtained image");
	displayer.consume(fproducer);

//	HistogramGDA gda(0);
//	gda.enableOutput(true, true);
//	gda.consume(fproducer);

	DescriptorWriter dw('s', 60, "test.txt");
	dw.setDescriptorCreator(createDescriptor);
	dw.postfix = "1.0 0.0 0.0";
	dw.consume(fproducer);

	fproducer.startProducing();
	return a.exec();
}
