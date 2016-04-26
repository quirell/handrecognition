#include "opencv2/opencv.hpp"
#include <vector>
#include <algorithm>
#include "HandColorPicker.h"
#include "BinarySegmentation.h"
using namespace cv;
using namespace std;


vector<Scalar> gatherMeanColors(VideoCapture cap,string windowName)
{
	Mat frame;
	cap >> frame;
	HandColorPicker hcp(Rect(0, 0, frame.size().width / 2, frame.size().height));
	for (int i = 0; i < 100;i++)
	{
		cap >> frame;
		flip(frame, frame, 1);
		hcp.drawHandPlaceSpot(frame);
		imshow(windowName, frame);
		if (waitKey(30) >= 0)
			break;
	}
	cap >> frame;
	flip(frame, frame, 1);
	cvtColor(frame, frame, COLOR_BGR2HLS);
	vector<Scalar> means = hcp.getMeanColors(frame);
	return means;
}

int main(int, char**)
{
	const String windowName = "edges";
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	Ptr<BackgroundSubtractorMOG2> bgSubtractor = cv::createBackgroundSubtractorMOG2(500,20,false);
//	Mat output;
	namedWindow(windowName);
	namedWindow("copy");
	Mat frame;
	cap >> frame;
	HandColorPicker hcp(Rect(0, 0, frame.size().width / 2, frame.size().height));
	BinarySegmentation bs(Scalar(2, 20, 20), Scalar(2, 20, 20));
	vector<Scalar> means = gatherMeanColors(cap, windowName);
//	setWindowProperty(windowName,CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
	int xxx = 0;
	for (;;)
	{	
		vector<vector<Point>> contours;
		cap >> frame; // get a new frame from camera
		flip(frame,frame, 1);
		Mat output;
//		Mat output1(Size((frame.size() / 2).width*7, (frame.size()/2).height),CV_8U);
//		dilate(frame, frame, Mat(Size(3, 3), CV_8U, Scalar(1, 1, 1)));
//		erode(frame, frame, Mat(Size(20,20),CV_8U, Scalar(1,1,1)));
//		int z = 0;
//		Mat prev;
//		for(Scalar mean : means)
//		{	
//
//			vector<Scalar> x = { mean };
//			bs.binarize(frame, output, x);
////			if(!prev.empty())
////			{
////				Mat diff = prev != output;
////				int nz = countNonZero(diff);
////			}
////			output.copyTo(prev);
////			dilate(output,output, Mat(Size(20, 20), CV_8U, Scalar(1, 1, 1)));
//			resize(output, output, frame.size() / 3);
//			output.copyTo(output1(Rect(Point(z,0), output.size())));
//			z += output.size().width;
//		}
		cvtColor(frame, frame,COLOR_BGR2HLS);
//		if(xxx++ < 100)
//			means = hcp.getMeanColors(frame);
		bs.binarize(frame, output, means);
//		int nz = countNonZero(output);
//		dilate(output,output, Mat(Size(6,6),CV_8U));
		medianBlur(output, output, 7);
		cvtColor(frame, frame,COLOR_HLS2BGR);

//		resize(output, output, frame.size() / 3);
//		output.copyTo(output1(Rect(Point(z, 0), output.size())));
//		hcp.drawMeanColors(frame);
//		hcp.drawHandPlaceSpot(frame);
//		Mat xx;
//		resize(output, output, output.size()/4);
//		Mat zz = frame(Rect(0, 0, xx.rows, xx.cols));
//		Mat output;
//		resize(output, output, frame.size() / 4);
//		Mat zz = frame(Rect(Point(0,0), output.size()));
//		output.copyTo(zz);
//		dilate(output, output, Mat(3,3,1));
//		erode(output, output, Mat(3,3,1));
//		blur(output, output, Size(20, 20));
//				bgSubtractor->apply(frame, output);
		imshow("copy", output);
//		blur(output, output,Size(3,3));
//		//erode(output, output, Mat());
//		dilate(output, output, Mat());
//		//Canny(output, output, 10,20, 3);
		findContours(output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		
		sort(contours.begin(), contours.end(), [=](vector<Point> x, vector<Point> y) -> double {return contourArea(y) < contourArea(x); });
		for (int i = 0; i < min((size_t)3,contours.size()) ;i++) {
			//if (contourArea(contours[i]) < 300)
			//	continue;
			//drawContours(frame, contours, i,Scalar(255,0,0));
			vector<Point> hull;
			convexHull(contours[i], hull);
			if (hull.size() > 0) {
				vector<vector<Point>> hs;
				hs.push_back(hull);
				drawContours(frame,hs , 0, Scalar(0, 0, 255));
			}
		}

		imshow(windowName, frame);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

