#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

#define MAX_DIGIT 2

int main() {

	//cv::Mat testimg = cv::Mat(cv::Size(960, 540), CV_8UC4, cv::Scalar(100, 100, 100));
	//cv::Mat testimg = cv::imread("pics/test.jpg");
	//cv::imshow("test", testimg);
	//cv::waitKey(0);
	//cv::destroyAllWindows();
	//cv::waitKey(0);

	//for (int i = 0; i < 5; i++) cout << "i = " << i << endl;
	//getchar();

	//

	string filename_old,numpart;
	//string filename_num;
	string filename_new;

	int rows_old, cols_old;
	int rows_new;
	double ratio;
	int marginrows;			//blackmarginの行の長さの片方分だけ

	Mat pic_old;

	fstream f_file;

	int num = 1;
	while (1) {	//画像の枚数だけ繰り返してほしい
		cout << "num = " << num << endl;


		//候補のnumpartの生成
		numpart = to_string(num);
		int c1 = numpart.size();
		//
		cout<<"numpart.size =" << c1 <<endl;
		//
		for (int i = 0; i < MAX_DIGIT - c1; i++) numpart = "0"+numpart;

		cout << "numpart = "<< numpart <<endl;

		//候補のfilename
		filename_old = "in_pic/" + numpart + ".jpg";

		f_file.open(filename_old, ios_base::in);							//fileの存在確認
		if (f_file.fail() != 1) {															// file was found
			f_file.close();
			cout << "file was found" << endl;

			pic_old = imread(filename_old);
			rows_old = pic_old.rows;
			cols_old = pic_old.cols;
			cout << "rows_old = " << rows_old << endl;
			cout << "cols_old = " << cols_old << endl;

			ratio = (double)rows_old / (double)cols_old;		//サイズチェック
			if (ratio >= 1) continue;		//問題なし	これがwhileを抜けるものなのかは微妙
			else {
				rows_new = (int)(cols_old * 1.25);		//変換後の比が，行:列=5:4となるようにする
				marginrows = (int)((rows_new - rows_old) / 2);

				Mat pic_new = Mat(Size(cols_old, rows_new), CV_8UC3, Scalar(0, 0, 0));				//真っ黒な画像(変換後の画像データ)の生成

				//画素の書き換え
				for (int i = 0; i < rows_old; i++) {
					for (int j = 0; j < cols_old; j++) {
						pic_new.at<Vec3b>(marginrows + i, j)[0] = pic_old.at<Vec3b>(i, j)[0];		//Blue		iとjが逆かも	配列のコピー忘れた
						pic_new.at<Vec3b>(marginrows + i, j)[1] = pic_old.at<Vec3b>(i, j)[1];		//Green
						pic_new.at<Vec3b>(marginrows + i, j)[2] = pic_old.at<Vec3b>(i, j)[2];		//Red
						//pic_new.at<Vec3b>(j, marginrows + i)[0] = pic_old.at<Vec3b>(j, i)[0];		//Blue		iとjが逆かも	配列のコピー忘れた
						//pic_new.at<Vec3b>(j, marginrows + i)[1] = pic_old.at<Vec3b>(j, i)[1];		//Green
						//pic_new.at<Vec3b>(j, marginrows + i)[2] = pic_old.at<Vec3b>(j, i)[2];		//Red


					}
				}

				//画像の保存
				filename_new = "out_pic/" + numpart+".jpg";
				imwrite(filename_new,pic_new);

			}

		}
		else {

			f_file.close();
			cout << "finished" << endl;
			break;
		}

		num++;
	}

	getchar();

	//


	return 0;
}