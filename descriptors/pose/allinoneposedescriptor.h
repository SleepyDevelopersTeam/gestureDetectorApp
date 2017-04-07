#ifndef ALLINONEPOSEDESCRIPTOR_H
#define ALLINONEPOSEDESCRIPTOR_H

#include <opencv/cv.h>
#include <vector>
#include "histogram/shadowpreproducer.h"
#include "common/backgrounddetector.h"
#include "abstractposedescriptor.h"
#include "histogramposedescriptor.h"
#include "histogram/histogramdrawer.h"

struct AllInOneDescriptorParams
{
	unsigned int histLength;
	bool drawHistogram;

	AllInOneDescriptorParams()
	    : histLength(20)
	    , drawHistogram(true)
	{}
};

class AllInOnePoseDescriptor : public AbstractPoseDescriptor
{
public:
	AllInOnePoseDescriptor(AllInOneDescriptorParams params = AllInOneDescriptorParams());
	virtual ~AllInOnePoseDescriptor() override;

	void write(std::ostream &to);
	std::vector<float>* getFeaturesVector();
	bool similarTo(AbstractPoseDescriptor &anotherDescriptor, double accuracy);

	void accumulateNext(cv::Mat& nextFrame);
	unsigned int featuresCount();

private:
	HistogramPoseDescriptor* hpd;
	ShadowPreproducer preproducer;
	BackgroundDetector* bgDetector;
	HistogramDrawer* drawer;
	std::vector<float>* features;

	AllInOneDescriptorParams p;
};

#endif // ALLINONEPOSEDESCRIPTOR_H
