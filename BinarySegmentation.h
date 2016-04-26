#include "opencv2/opencv.hpp"
#include <vector>
#pragma once
using namespace cv;
using namespace std;

class BinarySegmentation
{
private:
	Scalar lowerThreshold;
	Scalar upperThreshold;
	Scalar maxValue;
	tuple<Scalar, Scalar> bounds(Scalar sample);

public:
	BinarySegmentation(Scalar lowerThreshold, Scalar upperThreshold, Scalar maxValue = Scalar(255, 255, 255));
	~BinarySegmentation();
	void binarize(Mat input, OutputArray output, vector<Scalar> samples);
};

