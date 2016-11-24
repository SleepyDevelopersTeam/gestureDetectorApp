#include "consoleloggesturelistener.h"

ConsoleLogGestureListener::ConsoleLogGestureListener(std::ostream* console)
{
	this->console = console;
}

void ConsoleLogGestureListener::onGestureDetected(int gestureId)
{
	(*console) << "Gesture #" << gestureId << " detected!" << std::endl;
}
