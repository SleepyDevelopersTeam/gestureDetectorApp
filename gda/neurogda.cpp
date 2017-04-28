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
	// TODO: move that code of classification determination into NKPGD
	unsigned max_i = 0, submax_i = 1;
	std::cout << "output: ";
	for (unsigned i = 0; i < posesCount; i++)
	{
		float output = result[i];
		if (output > result[max_i])
		{
			submax_i = max_i;
			max_i = i;
		}
//		if (output >= outputPrintingThreshold)
//			std::cout << "Pose " << poseNames[i] << " / #" << i << " detected with probability of: " << output << std::endl;
		std::cout << output << "  ";
	}
	std::cout << std::endl;
	float max = result[max_i];
	float submax = result[submax_i];
	if (max > 0.5F && (max - submax) > (1 / 3.0F))
	{
		// this result is valuable
		std::cout << "CLASSIFICATION VERDICT: #" << max_i << std::endl;
	}
	else
	{
		std::cout << "CLASSIFICATION VERDICT: NONE" << std::endl;
	}
}
