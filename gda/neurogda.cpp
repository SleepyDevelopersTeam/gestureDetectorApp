#include "neurogda.h"

NeuroGDA::NeuroGDA(std::string nnFileName, unsigned int maxPoses, unsigned int totalKeyPosesCount)
{
	// gestureAccumulator = new KeyPoseGestureDescriptor(maxPoses, true);
	posesCount = totalKeyPosesCount;
	classifier = new NeuroClassifier(nnFileName, totalKeyPosesCount);
	outputPrintingThreshold = 0.6F;

	poseNames = new std::string[totalKeyPosesCount];
	for (unsigned i = 0; i < totalKeyPosesCount; i++)
	{
		poseNames[i] = "(unnamed)";
	}
}

NeuroGDA::~NeuroGDA()
{
//	if (gestureAccumulator != NULL)
//		delete gestureAccumulator;
	if (classifier != NULL)
		delete classifier;
}

void NeuroGDA::onPoseCandidate(AbstractPoseDescriptor *pose)
{
	float* result = classifier->run(pose);
	// TODO: add this to NeuroKPGDescriptor (now just printing out what it has)
	for (unsigned i = 0; i < posesCount; i++)
	{
		float output = result[i];
		if (output >= outputPrintingThreshold)
			std::cout << "Pose " << poseNames[i] << " / #" << i << " detected with probability of: " << output;
	}
}
