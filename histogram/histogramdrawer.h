#ifndef HISTOGRAMDRAWER_H
#define HISTOGRAMDRAWER_H

#include <opencv2/core.hpp>
#include "historgamshadowdescriptor.h"

class HistogramDrawer
{
public:
	HistogramDrawer(float horzAmount = 0.2F, float vertAmount = 0.2F);

	void draw (cv::Mat& shadow, HistorgamShadowDescriptor& descriptor);

	cv::Mat canvas;

	/**
	 * @brief Sets additional relative height of the image that will be used to display horizontal histogram
	 */
	float horzHistAmount;
	/**
	 * @brief Sets additional relative width of the image that will be used to display vertical histogram
	 */
	float vertHistAmount;
};

#endif // HISTOGRAMDRAWER_H
