#ifndef NEUROBSGDA_H
#define NEUROBSGDA_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "common/utils/displayframeconsumer.h"
#include "descriptors/pose/allinoneposedescriptor.h"
#include "neurogda.h"

class NeuroBSGDA : public NeuroGDA
{
public:
	NeuroBSGDA(std::__cxx11::string nnFileName, unsigned int maxPoses, unsigned int totalPosesCount);
	~NeuroBSGDA();

protected:
	void onNextFrameConsumed(cv::Mat& nextFrame) override;
	AllInOnePoseDescriptor* acc;
};

#endif // NEUROBSGDA_H
