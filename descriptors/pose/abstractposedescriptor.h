#ifndef ABSTRACTPOSEDESCRIPTOR_H
#define ABSTRACTPOSEDESCRIPTOR_H

class AbstractPoseDescriptor
{
public:
	AbstractPoseDescriptor();
	~AbstractPoseDescriptor();

	/**
	 * @brief Compares this descriptor to another with given accuracy parameter
	 * @param anotherDescriptor - the another descriptor
	 * @param accuracy - the accuracy parameter. Similarity will be defined according to its value.
	 * @return true if descriptors are similar enough to be considered describing the same pose
	 */
	virtual bool similarTo(AbstractPoseDescriptor& anotherDescriptor, double accuracy) = 0;
};

#endif // ABSTRACTPOSEDESCRIPTOR_H
