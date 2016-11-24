#ifndef APPCLOSEGESTURELISTENER_H
#define APPCLOSEGESTURELISTENER_H

#include "abstractgesturelistener.h"

class AppCloseGestureListener: public AbstractGestureListener
{
	Q_OBJECT
	
public:
	AppCloseGestureListener(int closeGestureId, int exitCode);
	
protected:
	void onGestureDetected(int gestureId);
	
private:
	int closeGesture;
	int exitCode;
};

#endif // APPCLOSEGESTURELISTENER_H
