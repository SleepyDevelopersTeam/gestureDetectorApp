#include "abstractgesturelistener.h"

AbstractGestureListener::AbstractGestureListener(QObject *parent):
	QObject(parent)
{
	gda = 0;
}

void AbstractGestureListener::listen(AbstractGDA *algo)
{
	if (gda != 0)
	{
		disconnect(gda, SIGNAL(gestureDetected(int)), this, SLOT(gestureDetected(int)));
	}
	gda = algo;
	if (algo != 0)
	{
		connect(gda, SIGNAL(gestureDetected(int)), this, SLOT(gestureDetected(int)));
	}
}

void AbstractGestureListener::gestureDetected(int gestureId)
{
	onGestureDetected(gestureId);
}

AbstractGestureListener::~AbstractGestureListener()
{
	
}
