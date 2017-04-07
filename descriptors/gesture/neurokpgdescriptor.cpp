#include "neurokpgdescriptor.h"
#include <cstddef>

NeuroKPGDescriptor::NeuroKPGDescriptor(unsigned int classesCount, unsigned int tailLength)
{
	accumulator = new float[classesCount * tailLength];
	cursor = 0;
	nclasses = classesCount;
	tail = tailLength;
}

NeuroKPGDescriptor::~NeuroKPGDescriptor()
{
	delete[] accumulator;
}

bool NeuroKPGDescriptor::similarTo(AbstractGestureDescriptor &anotherDescriptor)
{
	// TODO
	auto model = dynamic_cast <NeuroKPGDescriptor*> (&anotherDescriptor);
	if (model == NULL)
	{
		// type mismatch, => different descriptors
		return false;
	}
	return false;
}

void NeuroKPGDescriptor::putKeyPose(float *classifierOutput)
{

}

float* NeuroKPGDescriptor::getKeyPoseAt(unsigned int pos)
{
	return NULL;
}
