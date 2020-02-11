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

	{
		int aa;
		cin >> aa;
	}

	//cv::Mat testimg = cv::Mat(cv::Size(960, 540), CV_8UC4, cv::Scalar(200, 100, 100));
	//cv::imshow("test", testimg);
	//cv::waitKey(0);
	//cv::destroyAllWindows();
	//cv::waitKey(0);

	CTimeString time_;

	//std::cout << time_.getTimeString() << endl;

	//int aa;
	//std::cin >> aa;

	vector<string> filenames_;
	//string dir_ = "\../data/cut";
	string dir_ = "../../data/cut";
	time_.getFileNames_extension(dir_,filenames_,".png");

	for (int i = 0; i < filenames_.size(); i++) cout << i << ":" << filenames_[i] << endl;

	if(filenames_.size() == 0)
	{
		cout << "no file found" << endl;
		return 0;
	}

	{
		int aa;
		cin >> aa;
	}


	//cv::Mat::ptr p_image;
	cv::Mat image_test = cv::imread(dir_ + "/" + filenames_[0]);
	cv::Mat *p_image;
	//cv::namedWindow("Image", 0);
	cv::namedWindow("Image", 1);


	for (int i = 0; i < filenames_.size(); i++)
	{
		p_image = new cv::Mat(image_test.rows, image_test.cols, CV_8UC3, cvScalar(0, 0, 0));
		*p_image = cv::imread(dir_ + "/" + filenames_[i]);

		cv::imshow("Image", *p_image);
		cv::waitKey(1);

		int aa;
		cin >> aa;

		delete p_image;
	}

	{
		int aa;
		cin >> aa;
	}


	return 0;
}