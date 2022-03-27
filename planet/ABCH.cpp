#include"fly.h"

void position::A_analyse(Mat& src) {
	int threshold_min = 80;
	int sure_number = -1;
	circle_count.clear();
	for (int k = 0; k < rect_roi.size(); k++) {
		Mat srcImage;
		src(rect_roi[k]).copyTo(srcImage);
		Mat blur_srcImage;
		Mat gray_srcImage;

		vector<vector<Point>> roi_all_contours;
		/*模糊*/
		GaussianBlur(srcImage, blur_srcImage, Size(3, 3), 0, 0);
		medianBlur(blur_srcImage, blur_srcImage, 3);
		cvtColor(blur_srcImage, gray_srcImage, CV_RGB2GRAY);
		Canny(gray_srcImage, gray_srcImage, threshold_min, threshold_min * 3, 3, false);
		findContours(gray_srcImage, roi_all_contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);

		vector<vector<Point>> roi_ploy_contours(roi_all_contours.size());
		vector<RotatedRect>  myellispe(roi_all_contours.size());
		vector<Point2f> roi_ccs(roi_all_contours.size());
		vector<float> roi_radius(roi_all_contours.size());


		for (size_t s = 0; s < roi_all_contours.size(); s++) {
			approxPolyDP(Mat(roi_all_contours[s]), roi_ploy_contours[s], 3, true);
			minEnclosingCircle(roi_ploy_contours[s], roi_ccs[s], roi_radius[s]);
			/*if (roi_ploy_contours[s].size() > 5) {
				myellispe[s] = fitEllipse(roi_ploy_contours[s]);
			}*/
		}
		/*for (size_t m = 0; m < myellispe.size(); m++) {
			ellipse(srcImage, myellispe[m], Scalar(0, 0, 255), 1, 8);
		}*/
		for (size_t m = 0; m < roi_ccs.size(); m++)
		{
			circle(srcImage, roi_ccs[m], roi_radius[m], Scalar(0, 0, 255), 1, 8);
			circle(srcImage, roi_ccs[m], 1, Scalar(0, 255, 0), 2, 8);

		}
		imshow("圆检测", srcImage);
		waitKey(0);
		if (A_concentric(roi_ccs, roi_radius))  {
			sure_number = k;
		}
			//	Point2f  cen;
			//	vector<Point2f> cens;

			//	for (size_t m = 0; m < roi_ccs.size(); m++) {
			//		cen = roi_ccs[m];
			//		circle(srcImage, cen, 1, Scalar(0, 255, 0), 2, 8);
			//		cens.push_back(cen);
			//	}
			//	/*imshow("圆检测", srcImage);
			//	waitKey(0);*/
			//	int p = 0;
			//	for (size_t m = 0; m < cens.size(); m++) {
			//		for (size_t n = 0; n < cens.size(); n++) {
			//			p = p + point_compare(cens[m], cens[n]);
			//		}
			//	}
			//	if (p > 6) circle_count.push_back(p);
			//	else circle_count.push_back(0);
			//}
			//		/*int one_of_tar=0;
			//		for (size_t m = 0; m < cens.size(); m++) {
			//			for (size_t n = 0; n < cens.size(); n++) {
			//				p = p + point_compare(cens[m], cens[n]);
			//			}
			//			p = p - 1;
			//			if (p > 3) {
			//				one_of_tar = m;
			//				break;
			//			}
			//		}
			//		cout << "one of" << one_of_tar << endl;

			//		float minvalue = 0.5;
			//		float fixed_radius = 0;
			//		float ready_radius = 0;
			//		int e = 0;
			//		for (size_t m = 0; m < cens.size(); m++) {
			//			if (point_compare(cens[one_of_tar], cens[m])) {
			//				ready_radius = fabs(roi_radius[one_of_tar] - roi_radius[m]);
			//				if (fixed_radius == 0)

			//					continue;
			//				else
			//					if (ready_radius == fixed_radius) {
			//						fixed_radius = fabs(roi_radius[one_of_tar] - roi_radius[m]);
			//						e++;
			//					}
			//			}
			//		}
			//		cout << "e" << e << endl;
			//		if (e > 2) sure_number = k;*/
		}
	if (sure_number >=0) {
		/*vector<int>::iterator biggest = max_element(circle_count.begin(), circle_count.end());
		sure_number = distance(circle_count.begin(), biggest);*/
		rectangle(src, rect_roi[sure_number], Scalar(0, 255, 0), 2, 8);
		putText(src, "A", rect_roi[sure_number].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
		Rect target_roi = rect_roi[sure_number];
		target_a = Point2f((target_roi.tl().x + target_roi.br().x) / 2, (target_roi.tl().y + target_roi.br().y) / 2);
	}
}

bool position::A_concentric(vector<Point2f>ccs, vector<float>radius) {
	int h;
	int one_of_circle = -1;
	for (size_t i = 0; i < ccs.size(); i++) {
		h = 0;
		for (size_t j = 0; j < ccs.size(); j++) {
			if (point_compare(ccs[i], ccs[j]))
				h++;
		}
		if (h - 1 > 7) {
			one_of_circle = i;
			break;
		}
	}
	 
	/*找出所有同心圆*/
	vector<Point2f> ccs_concentirc;
	vector<float> radius_concentric;
	if (one_of_circle < 0) {
		return false;
	}
	else{
		for (size_t i = 0; i < ccs.size(); i++) {
			if (point_compare(ccs[one_of_circle], ccs[i]))
			{
				ccs_concentirc.push_back(ccs[i]);
				radius_concentric.push_back(radius[i]);
			}
		}
		return true; 
	}
}


int position::point_compare(Point2f a, Point2f b) {
	float accuracy = 0.5;
	if (fabs(a.x - b.x )< accuracy&&fabs(a.y - b.y < accuracy))
		return 1;
	else return 0;
}



void position::B_analyse(Mat& src) {
	for (int i=0; i < rect_roi.size(); i++) {
		Mat srcImage = src(rect_roi[i]);
		handle_image(srcImage);
		
	}
}


void::position::handle_image(Mat& srcImage) {
	Mat blur_src, gray_src;
	 
	/*medianBlur(srcImage, blur_src, 1);*/
	cvtColor(srcImage, gray_src, CV_BGR2GRAY);
	 
	threshold(gray_src, gray_src, 80, 245, THRESH_BINARY);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(1, 1));
	dilate(gray_src, gray_src,kernel);
	imshow("gray_src", gray_src);
	waitKey(0);

}
 