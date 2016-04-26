#include "opencv2/opencv.hpp"
#include <vector>
#pragma once
using namespace cv;
using namespace std;

class HandColorPicker
{
private:
	const double squareLen = 10;
	const double squareBorder = 1;
	const Scalar color = Scalar(0, 255, 0);
	static vector<Point2d> sizeDivisors;
	vector<Rect> squares;
public:
	HandColorPicker(Rect position);
	void drawHandPlaceSpot(Mat frame);
	void drawMeanColors(Mat frame);
	vector<Scalar> getMeanColors(Mat frame);

	Scalar getMeanColor(Mat frame, Rect square);
	
};
