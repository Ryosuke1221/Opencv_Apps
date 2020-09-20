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

enum KEYNUM
{
	EN_0 = 0,
	EN_1,
	EN_2,
	EN_3,
	EN_4,
	EN_5,
	EN_6,
	EN_7,
	EN_8,
	EN_9,
	EN_NONE
};

KEYNUM getKEYNUM()
{
	KEYNUM key_;
	short key_0 = GetAsyncKeyState(VK_NUMPAD0);	//0
	short key_1 = GetAsyncKeyState(VK_NUMPAD1);	//1
	short key_2 = GetAsyncKeyState(VK_NUMPAD2);	//2
	short key_3 = GetAsyncKeyState(VK_NUMPAD3);	//3
	short key_4 = GetAsyncKeyState(VK_NUMPAD4);	//4
	short key_5 = GetAsyncKeyState(VK_NUMPAD5);	//5
	short key_6 = GetAsyncKeyState(VK_NUMPAD6);	//6
	short key_7 = GetAsyncKeyState(VK_NUMPAD7);	//7
	short key_8 = GetAsyncKeyState(VK_NUMPAD8);	//8
	short key_9 = GetAsyncKeyState(VK_NUMPAD9);	//9
	if ((key_0 & 1) == 1) key_ = EN_0;
	else if ((key_1 & 1) == 1) key_ = EN_1;
	else if ((key_2 & 1) == 1) key_ = EN_2;
	else if ((key_3 & 1) == 1) key_ = EN_3;
	else if ((key_4 & 1) == 1) key_ = EN_4;
	else if ((key_5 & 1) == 1) key_ = EN_5;
	else if ((key_6 & 1) == 1) key_ = EN_6;
	else if ((key_7 & 1) == 1) key_ = EN_7;
	else if ((key_8 & 1) == 1) key_ = EN_8;
	else if ((key_9 & 1) == 1) key_ = EN_9;
	else key_ = EN_NONE;
	return key_;
}

int main()
{
	string dir_ = "../../data/test_image_separation";

	//input folder
	string folder_origin;
	vector<string> filenames_folder;
	{
		vector<string> filenames_folder_temp;
		CTimeString::getFileNames_folder(dir_, filenames_folder_temp);
		
		//check folder number
		if (filenames_folder_temp.size() > 10)
		{
			cout << "ERROR: too many folders readed" << endl;
			throw std::runtime_error("ERROR: too many folders readed");
		}
		else if (filenames_folder_temp.size() < 2)
		{
			cout << "ERROR: too few folders readed" << endl;
			throw std::runtime_error("ERROR: too few folders readed");
		}

		
		//input filenames_folder
		bool b_originFound = false;
		for (int j = 0; j < filenames_folder_temp.size(); j++)
		{
			if (filenames_folder_temp[j] == "_origin")
			{
				b_originFound = true;
				folder_origin = filenames_folder_temp[j];	// = _origin
				for (int i = 0; i < filenames_folder_temp.size(); i++)
				{
					if (i == j) continue;
					filenames_folder.push_back(filenames_folder_temp[i]);
				}
				break;
			}
		}
		if (!b_originFound)
		{
			cout << "ERROR: _origin(folder) not found" << endl;
			throw std::runtime_error("ERROR: _origin(folder) not found");
		}
	}

	//input image
	vector<string> filenames_img;
	{
		CTimeString::getFileNames_extension(dir_ + "/" + folder_origin, filenames_img, ".png");
		{
			//.jpg
			vector<string> filenames_jpg;
			CTimeString::getFileNames_extension(dir_ + "/" + folder_origin, filenames_jpg, ".jpg");
			for (int i = 0; i < filenames_jpg.size(); i++)
				filenames_img.push_back(filenames_jpg[i]);
		}
		if (filenames_img.size() == 0)
		{
			cout << "ERROR: no image file found" << endl;
			return 0;
		}
		cout << endl;
	}

	//cv::Mat image_test = cv::imread(dir_ + "/" + filenames_img[0]);
	cv::Mat image_test;
	string s_name_window = "temp";
	cv::namedWindow(s_name_window, cv::WINDOW_NORMAL);
	//cv::Mat *p_image;

	int index_img = 0;
	bool b_showing = false;

	cout << "filenames_img.size():" << filenames_img.size() << endl;

	const int cols_standard = 960;
	const int rows_standard = 540;
	const float aspect_ratio_standard = (float)cols_standard / (float)rows_standard;


	while (1)
	{
		KEYNUM key_ = getKEYNUM();

		if ((!(key_ == EN_0 || key_ == EN_NONE) && filenames_img.size() > index_img) || !b_showing)
		{
			image_test.release();
			image_test = cv::imread(dir_ + "/" + folder_origin + "/" + filenames_img[index_img]);
			int cols_, rows_;
			float ratio_size;
			if (aspect_ratio_standard <= (float)image_test.cols / (float)image_test.rows)
				ratio_size = (float)cols_standard / (float)image_test.cols;
			else
				ratio_size = (float)rows_standard / (float)image_test.rows;
			cols_ = (int)(ratio_size * image_test.cols);
			rows_ = (int)(ratio_size * image_test.rows);
			cv::resizeWindow(s_name_window, cols_, rows_);
			index_img++;
			b_showing = true;
		}
		if ((GetAsyncKeyState(VK_ESCAPE) & 1) == 1) break;
		cv::imshow(s_name_window, image_test);
		cv::waitKey(1);
	}

	//{
	//	cv::Mat *p_image_raw;
	//	cv::Mat *p_image_cut;

	//	int pos_leftup_u;
	//	int pos_leftup_v;
	//	int pos_rightdown_u;
	//	int pos_rightdown_v;
	//	int size_rows;
	//	int size_cols;

	//	int kataoka_PC = 0;

	//	cout << "Which are you using ? (kataoka_umelab:0, kataoka_home:1, other:2) :";

	//	cin >> kataoka_PC;

	//	//kataoka_umelab
	//	if (kataoka_PC == 0)
	//	{
	//		int which_screen = 0;

	//		cout << "Select which screen is needed (left:0, center:1, right:2) :";
	//		cin >> which_screen;

	//		if (which_screen == 0)
	//		{
	//			pos_leftup_u = 0;
	//			pos_leftup_v = 0;
	//			pos_rightdown_u = 1079;
	//			pos_rightdown_v = 1919;
	//		}

	//		else if (which_screen == 1)
	//		{
	//			pos_leftup_u = 1080;
	//			pos_leftup_v = 154;
	//			pos_rightdown_u = 3639;
	//			pos_rightdown_v = 1593;
	//		}

	//		else if (which_screen == 2)
	//		{
	//			pos_leftup_u = 3640;
	//			pos_leftup_v = 154;
	//			pos_rightdown_u = 6199;
	//			pos_rightdown_v = 1593;
	//		}
	//		else
	//		{
	//			cout << "ERROR: invalid command" << endl;
	//			return 0;
	//		}

	//	}

	//	//kataoka_home
	//	else if (kataoka_PC == 1)
	//	{
	//		int which_screen = 0;

	//		cout << "Select which screen is needed (left:0, right:1) :";
	//		cin >> which_screen;

	//		if (which_screen == 0)
	//		{
	//			pos_leftup_u = 0;
	//			pos_leftup_v = 0;
	//			pos_rightdown_u = 1919;
	//			pos_rightdown_v = 1079;
	//		}

	//		else if (which_screen == 1)
	//		{
	//			pos_leftup_u = 1920;
	//			pos_leftup_v = 0;
	//			pos_rightdown_u = 3839;
	//			pos_rightdown_v = 1079;
	//		}

	//		else
	//		{
	//			cout << "ERROR: invalid command" << endl;
	//			return 0;
	//		}
	//	}

	//	else if (kataoka_PC == 2)
	//	{
	//		cout << "pos_leftup_u = ";
	//		cin >> pos_leftup_u;
	//		cout << "pos_leftup_v = ";
	//		cin >> pos_leftup_v;
	//		cout << "pos_rightdown_u = ";
	//		cin >> pos_rightdown_u;
	//		cout << "pos_rightdown_v = ";
	//		cin >> pos_rightdown_v;
	//	}
	//	else
	//	{
	//		cout << "ERROR: invalid command" << endl;
	//		return 0;
	//	}


	//	Sleep(0.5 * 1000);
	//	//cout << "Press Enter to Start:" << endl;

	//	//GetAsyncKeyState(VK_RETURN);
	//	//while (1)
	//	//{
	//	//	if ((GetAsyncKeyState(VK_RETURN) & 1) == 1) break;
	//	//	//short key_num = GetAsyncKeyState(VK_RETURN);
	//	//	//if ((key_num & 1) == 1)	break;
	//	//}
	//	cout << "Start!!" << endl;

	//	size_cols = pos_rightdown_u - pos_leftup_u + 1;
	//	size_rows = pos_rightdown_v - pos_leftup_v + 1;

	//	for (int i = 0; i < filenames_.size(); i++)
	//	{
	//		p_image_raw = new cv::Mat(image_test.rows, image_test.cols, CV_8UC3, cvScalar(0, 0, 0));
	//		*p_image_raw = cv::imread(dir_ + "/" + filenames_[i]);
	//		p_image_cut = new cv::Mat(size_rows, size_cols, CV_8UC3, cvScalar(0, 0, 0));
	//		for (int rows_ = 0; rows_ < size_rows; rows_++)
	//		{
	//			cv::Vec3b *src_raw = p_image_raw->ptr<cv::Vec3b>(pos_leftup_v + rows_);
	//			cv::Vec3b *src_cut = p_image_cut->ptr<cv::Vec3b>(rows_);
	//			for (int cols_ = 0; cols_ < size_cols; cols_++)	
	//				src_cut[cols_] = src_raw[pos_leftup_u + cols_];//pointer?

	//		}

	//		//save image
	//		//https://www.sejuku.net/blog/58892
	//		//string filename_new = filenames_[i].substr(0, filenames_[i].size() - 4) + "_cut.png";
	//		string filename_new =
	//			filenames_[i].substr(0, filenames_[i].size() - 4)
	//			+ "_cut"
	//			+ filenames_[i].substr(filenames_[i].size() - 4, 4);
	//		cv::imwrite(dir_ + "/cut/" + filename_new, *p_image_cut);
	//		cout << "saved:" << filename_new << endl;
	//	}

	//	delete p_image_raw;
	//	delete p_image_cut;
	//}

	return 0;
}