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
		cout << "ERROR: no file found" << endl;
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

		int kataoka_PC = 0;

		cout << "Are you kataoka_PC in umelab? (yes:1, no:0) :";
		cin >> kataoka_PC;

		if (kataoka_PC == 1)
		{
			int which_screen = 0;

			cout << "Select which screen is needed (left:0, center:1, right:2) :";
			cin >> which_screen;

			if (which_screen == 0)
			{
				pos_leftup_u = 0;
				pos_leftup_v = 0;
				pos_rightdown_u = 1079;
				pos_rightdown_v = 1919;
			}
			else if (which_screen == 1)
			{
				pos_leftup_u = 1080;
				pos_leftup_v = 154;
				pos_rightdown_u = 3639;
				pos_rightdown_v = 1593;
			}

			else if (which_screen == 2)
			{
				pos_leftup_u = 3640;
				pos_leftup_v = 154;
				pos_rightdown_u = 6199;
				pos_rightdown_v = 1593;
			}
			else
			{
				cout << "ERROR: invalid command" << endl;
				return 0;
			}

		}

		else if (kataoka_PC == 0)
		{
			cout << "pos_leftup_u = ";
			cin >> pos_leftup_u;
			cout << "pos_leftup_v = ";
			cin >> pos_leftup_v;
			cout << "pos_rightdown_u = ";
			cin >> pos_rightdown_u;
			cout << "pos_rightdown_v = ";
			cin >> pos_rightdown_v;
		}
		else
		{
			cout << "ERROR: invalid command" << endl;
			return 0;
		}


		Sleep(0.5 * 1000);
		//cout << "Press Enter to Start:" << endl;

		//GetAsyncKeyState(VK_RETURN);
		//while (1)
		//{
		//	if ((GetAsyncKeyState(VK_RETURN) & 1) == 1) break;
		//	//short key_num = GetAsyncKeyState(VK_RETURN);
		//	//if ((key_num & 1) == 1)	break;
		//}
		cout << "Start!!" << endl;

		size_cols = pos_rightdown_u - pos_leftup_u + 1;
		size_rows = pos_rightdown_v - pos_leftup_v + 1;

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