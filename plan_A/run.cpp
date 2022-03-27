#include"fly.h"

using namespace cv;
using namespace std;

//void main() {
//	Mat src = imread("C:\\Users\\Lenovo\\Pictures\\DK12_side.bmp");
//	if (!src.data) {
//		cout << "ppp" << endl;
//	}
//	Mat dst;
//	threshold(src, dst, 200, 255, THRESH_BINARY);
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(55, 55));
//	morphologyEx(dst, dst, MORPH_OPEN, kernel);
//	Mat grat;
//	Canny(dst, grat, 3, true);
//	vector<vector<Point>> contours;
//	findContours(grat, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//	for (int i=0; i < contours.size(); i++) {
//		drawContours(grat, contours, i, Scalar(255,255,255), -1, 8);
//	}
//	 
//	 
//	position la;
//	la.B_detection(grat,src);
//	
//}


int main() {
	Mat src;
	/*VideoCapture cap(0);
	do{
		cap >> src;*/
	src = imread("C:\\Users\\Lenovo\\Pictures\\map.jpg.png");
	if (!src.data)
	{
		cout << "Image cannnt open!!\n" << endl;
		return -1;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);

	position pos;
	pos.run(src);

	imshow("src", src);
	waitKey(0);
	/*} while (true);*/
}



void::position::run(cv::Mat& src) {
	/*roi_cut(src);*/
	if (rect_roi.empty())
		cout << "未识别到区域" << endl;
	else {
	/*寻找A区*/
		A_analyse(src);
		circle(src, target_a, 1, Scalar(0, 0, 255), 1, 8);
		cout << "A区:" << endl;
		cout << target_a << endl;
		solve_diretion(target_a, src);
		show_A = true;
		//// 
		/////*寻找H区*/
		analyse_H(src);
		circle(src, target_h, 1, Scalar(0, 0, 255), 1, 8);
		cout << "H区:" << endl;
		cout << target_h << endl;
		solve_diretion(target_h, src);
		show_H = true;
		///////*寻找B区*/
		analyse_B(src);
		circle(src, target_b, 1, Scalar(0, 0, 255), 1, 8);
		cout << "B区:" << endl;
		cout << target_b << endl;
		solve_diretion(target_b, src);
		show_B = true;
		///////*寻找C区*/
		analyse_C(src);
		circle(src, target_c, 1, Scalar(0, 0, 255), 1, 8);
		cout << "C区:" << endl;
		cout << target_c << endl;
		solve_diretion(target_c, src);
		show_C = true;
		B_svm_analyse(src);
		imshow("src_assgin", src);
		waitKey(0);
	}
}
