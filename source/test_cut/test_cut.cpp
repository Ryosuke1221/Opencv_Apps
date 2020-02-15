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

	CTimeString time_;

	vector<string> filenames_;
	string dir_ = "../../data/test_cut";
	time_.getFileNames_extension(dir_,filenames_,".png");

	if(filenames_.size() == 0)
	{
		cout << "no file found" << endl;
		return 0;
	}

	cout << endl;

	cv::Mat image_test = cv::imread(dir_ + "/" + filenames_[0]);

	{
		cv::Mat *p_image_raw;
		cv::Mat *p_image_cut;

		int pos_leftup_u;
		int pos_leftup_v;
		int pos_rightdown_u;
		int pos_rightdown_v;
		int size_rows;
		int size_cols;

		//test
		cout << "pos_leftup_u = ";
		cin >> pos_leftup_u;
		cout << "pos_leftup_v = ";
		cin >> pos_leftup_v;
		cout << "pos_rightdown_u = ";
		cin >> pos_rightdown_u;
		cout << "pos_rightdown_v = ";
		cin >> pos_rightdown_v;

		Sleep(1 * 1000);
		cout << "Press Enter to Start:" << endl;

		GetAsyncKeyState(VK_RETURN);
		while (1)
		{
			if ((GetAsyncKeyState(VK_RETURN) & 1) == 1) break;
			//short key_num = GetAsyncKeyState(VK_RETURN);
			//if ((key_num & 1) == 1)	break;
		}
		cout << "Start!!" << endl;

		size_cols = pos_rightdown_u - pos_leftup_u;
		size_rows = pos_rightdown_v - pos_leftup_v;

		for (int i = 0; i < filenames_.size(); i++)
		{
			p_image_raw = new cv::Mat(image_test.rows, image_test.cols, CV_8UC3, cvScalar(0, 0, 0));
			*p_image_raw = cv::imread(dir_ + "/" + filenames_[i]);
			p_image_cut = new cv::Mat(size_rows, size_cols, CV_8UC3, cvScalar(0, 0, 0));
			for (int rows_ = 0; rows_ < size_rows; rows_++)
			{
				cv::Vec3b *src_raw = p_image_raw->ptr<cv::Vec3b>(pos_leftup_v + rows_);
				cv::Vec3b *src_cut = p_image_cut->ptr<cv::Vec3b>(rows_);
				for (int cols_ = 0; cols_ < size_cols; cols_++)	
					src_cut[cols_] = src_raw[pos_leftup_u + cols_];//pointer?

			}

			//save image
			//https://www.sejuku.net/blog/58892
			string filename_new = filenames_[i].substr(0, filenames_[i].size() - 4) + "_cut.png";
			cv::imwrite(dir_ + "/cut/" + filename_new, *p_image_cut);
			cout << "saved:" << filename_new << endl;
		}

		delete p_image_raw;
		delete p_image_cut;
	}

	return 0;
}