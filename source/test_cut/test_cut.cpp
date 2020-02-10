// Standard includes
#include<stdio.h>
#include<math.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>

//OpenCV include
#include<opencv2/opencv.hpp>

#include"TimeString.h"

int main() {

	//cv::Mat testimg = cv::Mat(cv::Size(960, 540), CV_8UC4, cv::Scalar(200, 100, 100));
	//cv::imshow("test", testimg);
	//cv::waitKey(0);
	//cv::destroyAllWindows();
	//cv::waitKey(0);

	CTimeString time_;

	std::cout << time_.getTimeString() << endl;

	int aa;
	std::cin >> aa;

	return 0;
}