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

//test_image_separation
//\ _origin
//\ _01
//\ _02
//\ _...

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

void setImage(cv::Mat &image_, string s_filename, string s_name_window, int cols_standard, int rows_standard, string s_txt = "")
{
	float aspect_ratio_standard = (float)cols_standard / (float)rows_standard;
	//input image
	image_.release();
	image_ = cv::imread(s_filename);
	//text
	//https://swallow-incubate.com/archives/blog/20190118/
	if(s_txt.size() != 0)
		cv::putText(image_, s_txt, cv::Point(0, (int)((image_.rows - 1) * 0.9)),
			cv::FONT_HERSHEY_SIMPLEX, 5., cv::Scalar(0, 255, 0), 10);
	int cols_, rows_;
	float ratio_size;
	if (aspect_ratio_standard <= (float)image_.cols / (float)image_.rows)
		ratio_size = (float)cols_standard / (float)image_.cols;
	else
		ratio_size = (float)rows_standard / (float)image_.rows;
	cols_ = (int)(ratio_size * image_.cols);
	rows_ = (int)(ratio_size * image_.rows);
	cv::resizeWindow(s_name_window, cols_, rows_);
}

bool doTask_once(string dir_)
{
	const int cols_standard = 960;
	const int rows_standard = 540;
	const float aspect_ratio_standard = (float)cols_standard / (float)rows_standard;

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
		string s_temp;
		filenames_folder.push_back(s_temp);
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
			return false;
		}
		cout << endl;
	}

	cv::Mat image_showing = cv::Mat(cv::Size(cols_standard, rows_standard), CV_8UC3, cv::Mat::AUTO_STEP);
	cv::Mat image_before = cv::Mat(cv::Size((int)(cols_standard * 0.5), (int)(rows_standard * 0.5)), CV_8UC3, cv::Mat::AUTO_STEP);
	cv::Mat image_after = cv::Mat(cv::Size((int)(cols_standard * 0.5), (int)(rows_standard * 0.5)), CV_8UC3, cv::Mat::AUTO_STEP);
	string s_name_window_showing = "Showing";
	string s_name_window_before = "Before";
	string s_name_window_after = "After";
	cv::namedWindow(s_name_window_showing, cv::WINDOW_NORMAL);
	cv::namedWindow(s_name_window_before, cv::WINDOW_NORMAL);
	cv::namedWindow(s_name_window_after, cv::WINDOW_NORMAL);

	int index_img = 0;
	bool b_first = true;

	while (1)
	{
		KEYNUM key_ = getKEYNUM();

		if ((key_ != EN_NONE && filenames_img.size() > index_img) || b_first)
		{
			//move image
			if (!b_first)
			{
				//copy: showing -> after
				setImage(image_after, dir_ + "/" + folder_origin + "/" + filenames_img[index_img],
					s_name_window_after, (int)(cols_standard * 0.5), (int)(rows_standard * 0.5), filenames_img[index_img]);
				if ((int)key_ > filenames_folder.size() || key_ == EN_0)
				{
					cv::putText(image_after, folder_origin, cv::Point((int)((image_after.cols - 1)* 0.9), (int)((image_after.rows - 1)* 0.9)),
						cv::FONT_HERSHEY_SIMPLEX, 5., cv::Scalar(255, 0, 0), 10);
					cout << folder_origin << " -> " << folder_origin << endl;
				}
				else
				{
					cv::putText(image_after, filenames_folder[(int)key_], cv::Point((int)((image_after.cols - 1)* 0.9), (int)((image_after.rows - 1)* 0.9)),
						cv::FONT_HERSHEY_SIMPLEX, 5., cv::Scalar(255, 0, 0), 10);
					string folder_move = filenames_folder[(int)key_];
					CTimeString::movefile(
						dir_ + "/" + folder_origin + "/" + filenames_img[index_img],
						dir_ + "/" + folder_move + "/" + filenames_img[index_img]);
					cout << folder_origin << " -> " << folder_move << endl;
					cout << endl;
				}
				index_img++;
				if (filenames_img.size() == index_img) break;
			}

			if (index_img % 5 == 0)
			{
				cout << "show folder" << endl;
				cout << "key:" << 0 << " " << folder_origin << endl;
				for (int j = 0; j < filenames_folder.size(); j++)
				{
					if (j == 0) continue;
					cout << "key:" << j << " " << filenames_folder[j] << endl;
				}
				cout << endl;
			}
			//input image
			setImage(image_showing, dir_ + "/" + folder_origin + "/" + filenames_img[index_img],
				s_name_window_showing, cols_standard, rows_standard, filenames_img[index_img]);
			cout << "showing:" << filenames_img[index_img] << endl;
			//read: before
			if (index_img + 1 < filenames_img.size())
				setImage(image_before, dir_ + "/" + folder_origin + "/" + filenames_img[index_img + 1],
					s_name_window_before, (int)(cols_standard * 0.5), (int)(rows_standard * 0.5));
			else
				image_before = cv::Mat(cv::Size((int)(cols_standard * 0.5), (int)(rows_standard * 0.5)), CV_8UC3, cv::Mat::AUTO_STEP);

			b_first = false;
		}
		if ((GetAsyncKeyState(VK_ESCAPE) & 1) == 1) break;
		cv::imshow(s_name_window_showing, image_showing);
		cv::imshow(s_name_window_before, image_before);
		cv::imshow(s_name_window_after, image_after);
		cv::waitKey(1);
	}
	cout << "finished" << endl;
	cv::destroyAllWindows();
	return true;
}

int main()
{

	string dir_ = "../../data/test_image_separation";

	while (1)
	{
		if (!doTask_once(dir_))
		{
			cout << "continue?  1:Yes  0:No" << endl;
			cout << "->";
			bool b_continue = true;
			cin >> b_continue;
			if (!b_continue) break;
		}
	}

	return 0;
}