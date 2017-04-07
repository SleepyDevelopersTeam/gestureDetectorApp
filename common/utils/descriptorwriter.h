#ifndef DESCRIPTORWRITER_H
#define DESCRIPTORWRITER_H

#include <string>
#include <opencv/cv.h>
#include <iostream>
#include <fstream>
#include "frameproducers/abstractframeproducer.h"
#include "gda/abstractgda.h"
#include "descriptors/pose/abstractposedescriptor.h"

class DescriptorWriter: public AbstractGDA
{
	Q_OBJECT

public:
	DescriptorWriter(char writeKey, int writeEveryNthFrame, std::string filename);

	void write(const cv::Mat& image);
	void onNextFrameConsumed(cv::Mat& nextFrame);
	void setDescriptorCreator(AbstractPoseDescriptor* (*creator)(cv::Mat&));

	~DescriptorWriter();

private:
	std::string filename;
	int interval;
	char wkey;
	AbstractFrameProducer* producer;
	int framesElapsed;
	std::ofstream file;

	AbstractPoseDescriptor* (*creator)(cv::Mat&);
};

#endif // DESCRIPTORWRITER_H
