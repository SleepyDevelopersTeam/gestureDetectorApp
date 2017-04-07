#include "descriptorwriter.h"
#include <vector>

std::string joinFeatures(std::vector<float>* features)
{
	std::stringstream ss;
	for(size_t i = 0; i < features->size(); ++i)
	{
		if(i != 0)
			ss << " ";
		ss << features->at(i);
	}
	return ss.str();
}

DescriptorWriter::DescriptorWriter(char writeKey, int writeEveryNthFrame, std::string filename)
{
	wkey = writeKey;
	interval = writeEveryNthFrame;
	this->filename = filename;
	this->producer = NULL;
	framesElapsed = 0;

	postfix = "0";

	file.open(filename);
}

DescriptorWriter::~DescriptorWriter()
{
	if (this->producer != NULL)
		delete this->producer;
	file.close();
}

void DescriptorWriter::onNextFrameConsumed(cv::Mat &nextFrame)
{
	++framesElapsed;
	// why it is created every frame? because it can be not stateless like all-in-one descriptor that accumulates background
	AbstractPoseDescriptor* desc = creator(nextFrame);
	if (framesElapsed % interval == 0)
	{
		if (desc != NULL)
		{
			std::vector<float>* features = desc->getFeaturesVector();
			std::string cat = joinFeatures(features);
			file << cat << std::endl;
			file << postfix << std::endl;
			std::cout << "Written to file: " << filename << std::endl;
			delete features;
		}
		else
		{
			std::cerr << "Warning: descriptor is null!" << std::endl;
		}
	}
	else
	{
		int left = interval - (framesElapsed % interval);
		if (left % 10 == 0)
			std::cerr << left << " ";
		if (left == 1)
			std::cerr << std::endl;
	}
}

void DescriptorWriter::setDescriptorCreator(AbstractPoseDescriptor *(*creator)(cv::Mat &))
{
	this->creator = creator;
}
