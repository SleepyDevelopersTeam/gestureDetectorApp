#ifndef KEYPOSEGESTUREDESCRIPTOR_H
#define KEYPOSEGESTUREDESCRIPTOR_H

#include "abstractgesturedescriptor.h"
#include "descriptors/pose/abstractposedescriptor.h"

class KeyPoseGestureDescriptor: public AbstractGestureDescriptor
{
public:
	KeyPoseGestureDescriptor(unsigned int N, bool isAccumulator = false);
	~KeyPoseGestureDescriptor();

	virtual bool similarTo(AbstractGestureDescriptor &anotherDescriptor);

	/**
	 * @brief Should be called on every PoseDescriptor obtained. Will internally check if
	 * it's a key pose and modify itself.
	 * @param The obtained descriptor.
	 * @return Whether the gesture descriptor was modified
	 */
	virtual bool appendPose(AbstractPoseDescriptor* keyPoseCandidate, double accuracy);

private:
	int* poses;
	unsigned int queueStart;
	unsigned int N;
	void pushToQueue(int next);
	int getPoseAt(unsigned int index);

	bool isAccumulator;
};

#endif // KEYPOSEGESTUREDESCRIPTOR_H
