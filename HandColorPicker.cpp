#include "HandColorPicker.h"


HandColorPicker::HandColorPicker(Rect position)
{
	for (Point2d p : HandColorPicker::sizeDivisors) {
		squares.push_back(Rect(position.x + position.width / p.x, position.y + position.height / p.y, squareLen, squareLen));
//		squares.push_back(Rect(position.x + position.width / p.x, position.y + position.height / p.y, squareLen, squareLen));
	}
}

void HandColorPicker::drawHandPlaceSpot(Mat frame) {
	for (Rect square: squares) {
		rectangle(frame,square,color,HandColorPicker::squareBorder);
	}
}


void HandColorPicker::drawMeanColors(Mat frame) {
	for (Rect square : squares) {
		square -= Size(HandColorPicker::squareBorder, HandColorPicker::squareBorder);
		frame(square).setTo(getMeanColor(frame, square));
	}
}

vector<Scalar> HandColorPicker::getMeanColors(Mat frame){
	vector<Scalar> meanColors;
	for (Rect square : squares) {
		meanColors.push_back(getMeanColor(frame,square));
	}
	return meanColors;
}

Scalar HandColorPicker::getMeanColor(Mat frame, Rect square) {
	Mat region = frame(square);
	Scalar meanColor = mean(region);
	return meanColor;
}

//vector<Point2d> HandColorPicker::sizeDivisors = { Point2d(3,4),Point2d(4,2),Point2d(3,1.5), Point2d(2, 2), Point2d(2.5, 2.5), Point2d(2, 1.5), Point2d(2.5, 1.8)};
vector<Point2d> HandColorPicker::sizeDivisors = { Point2d(4,2),Point2d(3,1.5), Point2d(2, 2), Point2d(2.5, 2.5), Point2d(2, 1.5), Point2d(2.5, 1.8)};