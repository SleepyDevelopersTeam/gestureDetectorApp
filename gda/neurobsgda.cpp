#include "neurobsgda.h"

NeuroBSGDA::NeuroBSGDA(std::string nnFileName, unsigned int maxPoses, unsigned int totalPosesCount)
    : NeuroGDA(nnFileName, maxPoses, totalPosesCount)
{
	acc = new AllInOnePoseDescriptor();
}

NeuroBSGDA::~NeuroBSGDA()
{
	delete acc;
}

void NeuroBSGDA::onNextFrameConsumed(cv::Mat &nextFrame)
{
	acc->accumulateNext(nextFrame);
	if (acc->featuresCount() != 0)
		onPoseCandidate(acc);
	// else bad features vector
}
