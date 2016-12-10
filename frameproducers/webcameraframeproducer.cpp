#include "webcameraframeproducer.h"

WebCameraFrameProducer::WebCameraFrameProducer()
{
	webcam = cvCreateCameraCapture(CV_CAP_ANY);
	if (webcam == 0) throw "No camera can be accessed!";
}

void WebCameraFrameProducer::startProducing()
{
	while (true)
	{
		lastFrameIpl = cvQueryFrame(webcam);
		lastFrame = cv::cvarrToMat(lastFrameIpl);
		onFrameGenerated(lastFrame);
		cvWaitKey(33);
	}
}

WebCameraFrameProducer::~WebCameraFrameProducer()
{
	
}
