#include "keyposegesturedescriptor.h"
#include "common/gesturelibrary.h"

KeyPoseGestureDescriptor::KeyPoseGestureDescriptor(unsigned int N, bool isAccumulator)
{
	this->N = N;
	queueStart = 0;
	poses = new int[N];
	for (unsigned i = 0; i < N; i++)
		poses[i] = -1;
	this->isAccumulator = isAccumulator;
}

bool KeyPoseGestureDescriptor::similarTo(AbstractGestureDescriptor &anotherDescriptor)
{
	KeyPoseGestureDescriptor *accumulator, *model;
	if (isAccumulator)
	{
		accumulator = this;
		model = dynamic_cast <KeyPoseGestureDescriptor*> (&anotherDescriptor);
		if (model == 0)
		{
			// type mismatch, => different descriptors
			return false;
		}
	}
	else
	{
		accumulator = dynamic_cast <KeyPoseGestureDescriptor*> (&anotherDescriptor);
		if (accumulator == 0)
		{
			// type mismatch, => different descriptors
			return false;
		}
		model = this;
	}

	bool result = false;
	for (unsigned i = 0; i < accumulator->N; i++)
	{
		bool matched = true;
		int acc_i = accumulator->getPoseAt(i);
		if (acc_i == -1)
		{
			// accumulator ended, there is no match
			result = false;
			break;
		}
		for (unsigned j = 0; j < model->N; j++)
		{
			int model_j = model->getPoseAt(j);
			if (model_j == -1)
			{
				// model has ended
				break;
			}
			if (model_j != acc_i)
			{
				// mismatch found
				matched = false;
				break;
			}
		}
		if (matched)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool KeyPoseGestureDescriptor::appendPose(AbstractPoseDescriptor *keyPoseCandidate, double accuracy)
{
	int poseIndex = GestureLibrary::matchPose(*keyPoseCandidate, accuracy);
	if (poseIndex != -1)
	{
		// key pose found
		pushToQueue(poseIndex);
		return true;
	}
	return false;
}

void KeyPoseGestureDescriptor::pushToQueue(int next)
{
	poses[queueStart] = next;
	++queueStart;
	if (queueStart >= N)
		queueStart = 0;
}
int KeyPoseGestureDescriptor::getPoseAt(unsigned int index)
{
	unsigned realIndex = queueStart + index;
	realIndex %= N;
	return poses[realIndex];
}

KeyPoseGestureDescriptor::~KeyPoseGestureDescriptor()
{
	delete poses;
}
