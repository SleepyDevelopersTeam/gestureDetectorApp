#include <QCoreApplication>

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
	return a.exec();
}
