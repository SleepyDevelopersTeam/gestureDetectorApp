#ifndef CONSOLELOGGESTURELISTENER_H
#define CONSOLELOGGESTURELISTENER_H

#include "abstractgesturelistener.h"
#include <iostream>

class ConsoleLogGestureListener: public AbstractGestureListener
{
	Q_OBJECT
public:
	ConsoleLogGestureListener(std::ostream* console);
	
protected:
	void onGestureDetected(int gestureId);
	
private:
	std::ostream* console;
};

#endif // CONSOLELOGGESTURELISTENER_H
