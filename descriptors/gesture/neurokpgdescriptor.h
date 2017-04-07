#ifndef NEUROKPGDESCRIPTOR_H
#define NEUROKPGDESCRIPTOR_H

#include "abstractgesturedescriptor.h"

class NeuroKPGDescriptor : public AbstractGestureDescriptor
{
public:
	NeuroKPGDescriptor(unsigned int classesCount, unsigned int tailLength);
	~NeuroKPGDescriptor();

	bool similarTo(AbstractGestureDescriptor &anotherDescriptor) override;

	void putKeyPose(float* classifierOutput);

protected:
	unsigned int nclasses;
	float* accumulator;

	float* getKeyPoseAt(unsigned int pos);

private:
	unsigned int cursor;
	unsigned int tail;
};

#endif // NEUROKPGDESCRIPTOR_H
