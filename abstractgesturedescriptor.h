#ifndef GESTUREDESCRIPTOR_H
#define GESTUREDESCRIPTOR_H

class AbstractGestureDescriptor
{
public:
	AbstractGestureDescriptor();
	~AbstractGestureDescriptor();
	
	virtual bool similarTo(AbstractGestureDescriptor& anotherDescriptor, double accuracy) = 0;
};

#endif // GESTUREDESCRIPTOR_H
