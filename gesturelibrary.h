#ifndef GESTURELIBRARY_H
#define GESTURELIBRARY_H

#include "abstractgesturedescriptor.h"

class GestureLibrary
{
public:
	GestureLibrary();
	
	int addGesture(AbstractGestureDescriptor& desc);
};

#endif // GESTURELIBRARY_H
