#include "BinarySegmentation.h"



BinarySegmentation::BinarySegmentation(Scalar lowerThreshold, Scalar upperThreshold,Scalar maxValue)
{
	this->lowerThreshold = lowerThreshold;
	this->upperThreshold = upperThreshold;
	this->maxValue = maxValue;
}


BinarySegmentation::~BinarySegmentation()
{
}

void BinarySegmentation::binarize(Mat input,OutputArray output, vector<Scalar> samples)
{	
	bool first = true;
	Mat binarized(input.size(),CV_8U);
	for (Scalar sample : samples) {
		tuple<Scalar, Scalar> lowerUpper = bounds(sample);
		inRange(input, get<0>(lowerUpper),get<1>(lowerUpper), binarized);
		if (first) {
			binarized.copyTo(output);
			first = false;
		}
		else
			add(binarized, output, output);
	}
}

tuple<Scalar, Scalar> BinarySegmentation::bounds(Scalar sample)
{
	Scalar lowerBound = sample - lowerThreshold;
	Scalar upperBound = sample + upperThreshold;
	for (int i = 0; i < 3; i++) {
		if (lowerBound[i] < 0)
			lowerBound[i] = sample[i];
		if (upperBound[i] > maxValue[i])
			upperBound[i] = maxValue[i]-upperBound[i];
	}
	return tuple<Scalar,Scalar>(lowerBound, upperBound);
}
