#include <QCoreApplication>

#include "frameproducers/webcameraframeproducer.h"
#include "common/utils/displayframeconsumer.h"
#include "gda/histogramgda.h"

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

//	DisplayFrameConsumer displayer("Obtained image");
//	displayer.consume(fproducer);

	HistogramGDA gda(0);
	gda.enableOutput(true, true);
	gda.consume(fproducer);

	fproducer.startProducing();
	return a.exec();
}
