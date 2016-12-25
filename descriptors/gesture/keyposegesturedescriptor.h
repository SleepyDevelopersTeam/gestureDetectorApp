#ifndef KEYPOSEGESTUREDESCRIPTOR_H
#define KEYPOSEGESTUREDESCRIPTOR_H

#include "abstractgesturedescriptor.h"
#include "descriptors/pose/abstractposedescriptor.h"

class KeyPoseGestureDescriptor: public AbstractGestureDescriptor
{
public:
	KeyPoseGestureDescriptor(unsigned int N);
	~KeyPoseGestureDescriptor();

	bool similarTo(AbstractGestureDescriptor &anotherDescriptor, double accuracy);

	/**
	 * @brief Should be called on every PoseDescriptor obtained. Will internally check if
	 * it's a key pose and modify itself.
	 * @param The obtained descriptor.
	 */
	void appendPose(AbstractPoseDescriptor* keyPoseCandidate);

private:
	AbstractPoseDescriptor** poses;
	unsigned int queueStart;
	unsigned int N;
	void pushToQueue(AbstractPoseDescriptor* next);
	AbstractPoseDescriptor* getPoseAt(unsigned int index);
};

#endif // KEYPOSEGESTUREDESCRIPTOR_H
