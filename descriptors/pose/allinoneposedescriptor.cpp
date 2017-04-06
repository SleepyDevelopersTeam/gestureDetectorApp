#include "allinoneposedescriptor.h"

AllInOnePoseDescriptor::AllInOnePoseDescriptor(AllInOneDescriptorParams params)
{
	bgDetector = 0;
	features = new std::vector<float>();
	p = params;
}

AllInOnePoseDescriptor::~AllInOnePoseDescriptor()
{
	delete features;
	delete bgDetector;
}

void AllInOnePoseDescriptor::accumulateNext(cv::Mat& nextFrame)
{
	if (bgDetector == 0)
	{
		bgDetector = new BackgroundDetector(nextFrame.size().width, nextFrame.size().height);
	}
	cv::Mat grayscale = cv::Mat(nextFrame.rows, nextFrame.cols, CV_8UC1, cv::Scalar(0, 0, 0));
	// cv::Mat test = cv::Mat(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0, 0, 0));
	cv::cvtColor(nextFrame, grayscale, CV_BGR2GRAY, 1);
	cv::GaussianBlur(grayscale, grayscale, cv::Size(9,9), 3);
	bgDetector->accumulate(&grayscale);
	bgDetector->getForegroundMask(grayscale);

	preproducer.preproduce(grayscale);

	cv::Rect2i largestBlob = preproducer.findLargestBlob(grayscale);
	features->clear();
	if (largestBlob.width > 0 && largestBlob.height > 0)
	{
		cv::Mat blob = grayscale(largestBlob);
		auto keyPoseCandidate = new HistogramPoseDescriptor(100);
		keyPoseCandidate->createFrom(blob);

		// quality-referred features
		features->push_back(bgDetector->lastFrameTrackedPixelsAmount);

		float area = (float) grayscale.size().area();
		float blobSize = largestBlob.area() / area;
		features->push_back(blobSize);

		features->push_back(preproducer.blobsProportion);
		features->push_back(preproducer.removedBlobsRelativeSize);
		features->push_back(preproducer.removedPixelsCount / area);

		unsigned len = keyPoseCandidate->getHorizontal()->getLength();
		for (unsigned i = 0; i < len; i++)
		{
			features->push_back(keyPoseCandidate->getHorizontal()->at(i));
		}
		len = keyPoseCandidate->getVertical()->getLength();
		for (unsigned i = 0; i < len; i++)
		{
			features->push_back(keyPoseCandidate->getVertical()->at(i));
		}
	}
}

std::vector<float>* AllInOnePoseDescriptor::getFeaturesVector()
{
	return new std::vector<float>(*features);
}

bool AllInOnePoseDescriptor::similarTo(AbstractPoseDescriptor &anotherDescriptor, double accuracy)
{
	// TODO:
	return false;
}

// TODO: or not?
void AllInOnePoseDescriptor::write(std::ostream &to)
{

}

unsigned int AllInOnePoseDescriptor::featuresCount()
{
	return features->size();
}
