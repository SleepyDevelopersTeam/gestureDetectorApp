#ifndef GESTUREDESCRIPTOR_H
#define GESTUREDESCRIPTOR_H

class AbstractGestureDescriptor
{
public:
	AbstractGestureDescriptor();
	~AbstractGestureDescriptor();
	
	/**
	 * @brief Compares this descriptor to another with given accuracy parameter
	 * @param anotherDescriptor - the another descriptor
	 * @param accuracy - the accuracy parameter. Similarity will be defined according to its value.
	 * @return true if descriptors are similar enough to be considered describing the same gesture
	 */
	virtual bool similarTo(AbstractGestureDescriptor& anotherDescriptor) = 0;
};

#endif // GESTUREDESCRIPTOR_H
