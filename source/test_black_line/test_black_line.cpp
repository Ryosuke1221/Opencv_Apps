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

	int width_line = 3;

	CTimeString time_;

	vector<string> filenames_;
	string dir_ = "../../data/test_black_line";
	CTimeString::getFileNames_extension(dir_, filenames_, ".png");
	{
		//.jpg
		vector<string> filenames_jpg;
		CTimeString::getFileNames_extension(dir_, filenames_jpg, ".jpg");
		for (int i = 0; i < filenames_jpg.size(); i++)
			filenames_.push_back(filenames_jpg[i]);
	}

	if(filenames_.size() == 0)
	{
		cout << "ERROR: no file found" << endl;
		return 0;
	}

	cout << endl;

	//cv::Mat image_test = cv::imread(dir_ + "/" + filenames_[0]);

	{
		//cv::Mat *p_image_raw;
		cv::Mat image_raw;

		//Sleep(0.5 * 1000);
		cout << "Start!!" << endl;

		for (int i = 0; i < filenames_.size(); i++)
		{
			//int rows_size = image_test.rows;
			//int cols_size = image_test.cols;

			//p_image_raw = new cv::Mat(rows_size, cols_size, CV_8UC3, cvScalar(0, 0, 0));
			//*p_image_raw = cv::imread(dir_ + "/" + filenames_[i]);
			cv::Mat image_raw = cv::imread(dir_ + "/" + filenames_[i]);

			int rows_size = image_raw.rows;
			int cols_size = image_raw.cols;

			//up
			for (int rows_ = 0; rows_ < 3; rows_++)
			{
				//cv::Vec3b *src_raw = p_image_raw->ptr<cv::Vec3b>(rows_);
				cv::Vec3b *src_raw = image_raw.ptr<cv::Vec3b>(rows_);
				for (int cols_ = 0; cols_ < cols_size; cols_++)
				{
					src_raw[cols_][0] = 0;
					src_raw[cols_][1] = 0;
					src_raw[cols_][2] = 0;
				}
			}
			//down
			for (int rows_ = rows_size - 3; rows_ < rows_size; rows_++)
			{
				//cv::Vec3b *src_raw = p_image_raw->ptr<cv::Vec3b>(rows_);
				cv::Vec3b *src_raw = image_raw.ptr<cv::Vec3b>(rows_);
				for (int cols_ = 0; cols_ < cols_size; cols_++)
				{
					src_raw[cols_][0] = 0;
					src_raw[cols_][1] = 0;
					src_raw[cols_][2] = 0;
				}
			}
			//left
			for (int rows_ = 3; rows_ < rows_size - 3; rows_++)
			{
				//cv::Vec3b *src_raw = p_image_raw->ptr<cv::Vec3b>(rows_);
				cv::Vec3b *src_raw = image_raw.ptr<cv::Vec3b>(rows_);
				for (int cols_ = 0; cols_ < 3; cols_++)
				{
					src_raw[cols_][0] = 0;
					src_raw[cols_][1] = 0;
					src_raw[cols_][2] = 0;
				}
			}
			//right
			for (int rows_ = 3; rows_ < rows_size - 3; rows_++)
			{
				//cv::Vec3b *src_raw = p_image_raw->ptr<cv::Vec3b>(rows_);
				cv::Vec3b *src_raw = image_raw.ptr<cv::Vec3b>(rows_);
				for (int cols_ = 0; cols_ < cols_size; cols_++)
					for (int cols_ = cols_size - 3; cols_ < cols_size; cols_++)
					{
						src_raw[cols_][0] = 0;
						src_raw[cols_][1] = 0;
						src_raw[cols_][2] = 0;
					}
			}

			//save image
			//https://www.sejuku.net/blog/58892
			string filename_new =
				filenames_[i].substr(0, filenames_[i].size() - 4)
				+ "_line"
				+ filenames_[i].substr(filenames_[i].size() - 4, 4);
			//cv::imwrite(dir_ + "/line/" + filename_new, *p_image_raw);
			cv::imwrite(dir_ + "/line/" + filename_new, image_raw);
			cout << "saved:" << filename_new << endl;
		}

		//delete p_image_raw;
	}

	return 0;
}