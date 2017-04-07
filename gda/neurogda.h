#ifndef NEUROGDA_H
#define NEUROGDA_H

#include <string>
#include <vector>
#include <opencv/cv.h>
#include "abstractgda.h"
#include "descriptors/pose/abstractposedescriptor.h"
#include "descriptors/gesture/keyposegesturedescriptor.h"
#include "neuro/neuroclassifier.h"

class NeuroGDA : public AbstractGDA
{
	Q_OBJECT

public:
	NeuroGDA(std::string nnFileName, unsigned int maxPoses, unsigned int totalKeyPosesCount);
	~NeuroGDA();

	float outputPrintingThreshold;
	std::string* poseNames;

protected:
	NeuroClassifier* classifier;
	void onPoseCandidate(AbstractPoseDescriptor* pose);
	unsigned int posesCount;
	virtual void onNextFrameConsumed(cv::Mat& nextFrame) = 0;

private:
	KeyPoseGestureDescriptor* gestureAccumulator;
};

#endif // NEUROGDA_H
