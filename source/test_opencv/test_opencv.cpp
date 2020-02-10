// Standard includes
#include<stdio.h>
#include<math.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>

//OpenCV include
#include<opencv2/opencv.hpp>

int main() {

	cv::Mat testimg = cv::Mat(cv::Size(960, 540), CV_8UC4, cv::Scalar(200, 100, 100));
	cv::imshow("test", testimg);
	cv::waitKey(0);
	cv::destroyAllWindows();
	cv::waitKey(0);

	return 0;
}