#ifndef NEUROCLASSIFIER_H
#define NEUROCLASSIFIER_H

#include <string>
#include <vector>
#include <fann.h>
#include <floatfann.h>
#include "descriptors/pose/abstractposedescriptor.h"

class NeuroClassifier
{
public:
	NeuroClassifier(std::string filename, unsigned int outputSize);
	~NeuroClassifier();

	float* run(AbstractPoseDescriptor* pose);

private:
	struct fann* nn;
	unsigned int nout;
};

#endif // NEUROCLASSIFIER_H
