#include "appclosegesturelistener.h"
#include <QCoreApplication>

AppCloseGestureListener::AppCloseGestureListener(int closeGestureId, int exitCode = 0)
{
	closeGesture = closeGestureId;
	this->exitCode = exitCode;
}

void AppCloseGestureListener::onGestureDetected(int gestureId)
{
	if (gestureId == closeGesture) {
		QCoreApplication::instance()->exit(exitCode);
	}
}
