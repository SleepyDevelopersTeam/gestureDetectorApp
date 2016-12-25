#ifndef HISTORGAMGESTUREDESCRIPTOR_H
#define HISTORGAMGESTUREDESCRIPTOR_H

#include "abstractgesturedescriptor.h"

class HistorgamGestureDescriptor: public AbstractGestureDescriptor
{
public:
	HistorgamGestureDescriptor();
	~HistorgamGestureDescriptor();
	
	bool similarTo(AbstractGestureDescriptor &anotherDescriptor, double accuracy);
};

#endif // HISTORGAMGESTUREDESCRIPTOR_H
