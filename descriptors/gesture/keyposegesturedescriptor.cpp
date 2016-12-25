#include "keyposegesturedescriptor.h"
#include "common/gesturelibrary.h"

KeyPoseGestureDescriptor::KeyPoseGestureDescriptor(unsigned int N)
{
	this->N = N;
	queueStart = 0;
	poses = new AbstractPoseDescriptor* [N];
}

bool KeyPoseGestureDescriptor::similarTo(AbstractGestureDescriptor &anotherDescriptor, double accuracy)
{
	// TODO
	return false;
}

void KeyPoseGestureDescriptor::appendPose(AbstractPoseDescriptor *keyPoseCandidate)
{
	// TODO
}

void KeyPoseGestureDescriptor::pushToQueue(AbstractPoseDescriptor *next)
{
	auto throwAway = poses[queueStart];
	if (throwAway)
		delete throwAway;
	poses[queueStart] = next;
	++queueStart;
	if (queueStart >= N)
		queueStart = 0;
}
AbstractPoseDescriptor* KeyPoseGestureDescriptor::getPoseAt(unsigned int index)
{
	// TODO
	return 0;
}

KeyPoseGestureDescriptor::~KeyPoseGestureDescriptor()
{
	// TODO
}
