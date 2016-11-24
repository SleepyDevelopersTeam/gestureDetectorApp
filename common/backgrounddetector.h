#ifndef BACKGROUNDDETECTOR_H
#define BACKGROUNDDETECTOR_H

#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <stdio.h>

class BackgroundDetector
{
public:
	BackgroundDetector(size_t height, size_t width);
	
	cv::Mat* meanAccumulator;
	cv::Mat* dispAccumulator;
	cv::Mat* n;
	
	cv::Mat* tracked;
	
	int width, height;
	
	// amount of pixels out of fone at which we need to recalculate fone
	float trackedPixelsThreshold;
	
	static int dispThreshold;
	static int maxN;
	static int forceLearnDuration;
	
	bool forceFoneAccumulating;
	int forceLearnFrameCounter;
	void enableForceAccumulating();
	void disableForceAccumulating();
	
	void accumulate(cv::Mat* nextFrame);
	void tracking(cv::Mat* nextFrame);
	void getForegroundMask(cv::Mat& thresholded);
	void getBackgroundMask(cv::Mat& thresholded);
	void accumulateAndTrack(cv::Mat *nextFrame);
	
	~BackgroundDetector();
};

#endif // BACKGROUNDDETECTOR_H
