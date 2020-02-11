// Standard includes
#include<stdio.h>
#include<math.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>

//OpenCV include
#include<opencv2/opencv.hpp>

//using namespace cv;
//using namespace std;

void my_mouse_callback(int event, int x, int y, int flags, void*param) {
	cv::Mat* image = static_cast<cv::Mat*>(param);

	switch (event) {
	case cv::EVENT_LBUTTONDOWN:
		std::cout << "(x, y) = (" << x << ", " << y << ")" << std::endl;
		break;
	}

}

int main() {

	std::string name = "mouse window";
	cv::Mat winmat(cv::Size(960, 540), CV_8UC3, cv::Scalar(100, 100, 100));
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE);

	cv::setMouseCallback(name, my_mouse_callback, (void *)&winmat);

	while (1) {

		//cv::imshow(name, winmat);
		if (cv::waitKey(1) == 27) break;		//Esc
	}

	//cv::Mat testimg;
	//testimg = cv::imread("pics/test.jpg");
	//cv::imshow("test", testimg);
	//cv::waitKey(0);
	//cv::destroyAllWindows();
	//cv::waitKey(0);
	
	return 0;
}

