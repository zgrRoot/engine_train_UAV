#include"fly.h"

using namespace cv;
using namespace std;

//int threshold_min=80;
 
//bool roi_sort(const Rect& a, const Rect& b);
 

int main(){
	Mat src;
	/*VideoCapture cap(0);*/
	
	/*do{*/
		 
		//cap >> src;
		//resize(src, src, Size(800, 800));
		src = imread("C:\\Users\\Lenovo\\Pictures\\map.jpg.png");
		//src = imread("C:\\Users\\Lenovo\\Pictures\\w_demo.jpg.png");
		 
		if (!src.data)
		{
			cout << "Í¼Ïñ¶ÁÈ¡Ê§°Ü£¡£¡\n" << endl;
			return -1;
		}
		namedWindow("src",CV_WINDOW_AUTOSIZE);
		 
		position pos;
		pos.run(src);

		imshow("src", src);
		waitKey(0);
 
	/* 
	} while (true);*/
}



void::position::run(cv::Mat& src) {
	roi_cut(src);
	///*Æ¥ÅäBÇø*/
	// 
	//Match_imge(handle_src, temp_b,temLoc_b);
	//rectangle(src, Rect(temLoc_b.x, temLoc_b.y, temp_b.cols, temp_b.rows), Scalar(0, 255, 0), 2, 8);
	//putText(src,"B", temLoc_b, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
	//roi_match_b(temLoc_b,temp_b,target_b,src);
	//
	///*Æ¥ÅäHÇø*/
	//Match_imge(handle_src, temp_h, temLoc_h);
	//rectangle(src, Rect(temLoc_h.x, temLoc_h.y, temp_h.cols, temp_h.rows), Scalar(0, 255, 0), 2, 8);
	//putText(src, "H", temLoc_h, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
	//roi_match_h(temLoc_h, temp_h, target_h, src);

	// 
	///*Æ¥ÅäCÇø*/
	//Match_imge(handle_src, temp_c, temLoc_c);
	//rectangle(src, Rect(temLoc_c.x, temLoc_c.y, temp_c.cols, temp_c.rows), Scalar(0, 255, 0), 2, 8);
	//putText(src, "C", temLoc_c, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
	//roi_match_c(temLoc_c, temp_c, target_c, src);
	//
	/*Ñ°ÕÒAÇø*/
	/*A_analyse(src);
	circle(src, target_a, 1, Scalar(0, 0, 255), 1, 8);
	cout << "AÇø:" << endl;
	cout << target_a << endl;
	solve_diretion(target_a, src);
	show_A = true;*/
	// 
	///*Ñ°ÕÒHÇø*/
	analyse_H(src);
	//for (int t = 0; t < rect_roi.size(); t++) {
	//	/*rectangle(src, rect_roi[t], Scalar(0, 0, 255), 1, 8);*/
	//	Mat ROI_img = src(rect_roi[t]);
	//	imshow("ssss", ROI_img);
	//	waitKey(1);
	//}
	///*Ñ°ÕÒBÇø*/
	analyse_B(src);
	///*Ñ°ÕÒCÇø*/
	/*analyse_C(src);*/
	//


	/*B_svm_analyse(src);*/

	
	///*H¡¢AÇøSVM*/
	/*svm_HA(src);*/

	/*B_analyse(src);*/

	 






	///*»æÖÆÂÖÀª*/
	//Mat dst = Mat::zeros(src.size(), src.type());
	//Point2f vertics[4];
	//for (size_t i = 0; i < map_contours.size(); i++) {
	//	circle(dst, ccs[i], radius[i], Scalar(255, 255, 255), 1.8);
	//	rect_contours[i].points(vertics);
	//	for (int m = 0; m < 4; m++) {
	//		line(dst, vertics[m], vertics[(m + 1) % 4], Scalar(255, 0, 255), 1, 8);
	//	}

	//}
	//imshow("dst", dst);
	imshow("src_assgin", src);
 }
	 
