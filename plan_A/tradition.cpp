#include"fly.h"
void position::preprocessing(Mat& src) {
	Mat srcImage;
	src.copyTo(srcImage);
	GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0);
	medianBlur(srcImage, srcImage, 3);
	Mat se = getStructuringElement(MORPH_RECT, Size(1, 1), Point(-1, -1));
	morphologyEx(srcImage, srcImage, MORPH_OPEN, se);


	cvtColor(srcImage, srcImage, CV_RGB2GRAY);
	Canny(srcImage, srcImage, 100, 240, 3, false);

}

void position::analyse_H(Mat& src) {

	Mat src_h;
	src.copyTo(src_h);


	GaussianBlur(src_h, src_h, Size(3, 3), 0, 0);
	medianBlur(src_h, src_h, 3);
	Mat se = getStructuringElement(MORPH_RECT, Size(1, 1), Point(-1, -1));
	morphologyEx(src_h, src_h, MORPH_OPEN, se);
	cvtColor(src_h, src_h, CV_RGB2GRAY);
	Canny(src_h, src_h, 100, 240, 3, false);
	vector<vector<Point>> rect_contours;
	findContours(src_h, rect_contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	/*Mat dst = Mat::zeros(src.size(), src.type());
	for (size_t i = 0; i < rect_contours.size(); i++) {
		drawContours(dst, rect_contours, i, Scalar(255, 0, 0), 1, 8);
	}
*/
	vector<vector<Point>> rect_may(rect_contours.size());
	vector<RotatedRect> ploy_contours(rect_contours.size());

	float maxarea = 100;//矩形区域最大面积
	float aspect_ratio = 0.8;//矩形区域长宽比


	for (size_t i = 0; i < rect_contours.size(); i++) {
		approxPolyDP(Mat(rect_contours[i]), rect_may[i], 3, true);
		double area = fabs(contourArea(rect_may[i]));
		if (isContourConvex(rect_may[i]) && rect_may[i].size() == 4 &&
			area > maxarea)
			ploy_contours[i] = minAreaRect(rect_may[i]);
	}

	vector<RotatedRect> area_h;//H区
	area_h.clear();
	vector<RotatedRect> area_bore;//障碍区
	Point2f target_bore;
	area_bore.clear();

	/*判断矩形区域长宽比*/
	for (size_t t = 0; t < ploy_contours.size(); t++) {
		float ratio;
		if (ploy_contours[t].size.width > ploy_contours[t].size.height)
			ratio = ploy_contours[t].size.height / ploy_contours[t].size.width;
		else
			ratio = ploy_contours[t].size.width / ploy_contours[t].size.height;
		if (ratio > aspect_ratio)
			area_h.push_back(ploy_contours[t]);
		if (fabs(ratio - 0.7) < 0.01)
			area_bore.push_back(ploy_contours[t]);
	}

	/*绘制H区*/
	Point2f verct[4];
	for (size_t m = 0; m < area_h.size(); m++) {
		area_h[m].points(verct);
		for (int j = 0; j < 4; j++) {
			line(src, verct[j], verct[(j + 1) % 4], Scalar(0, 255, 0), 2, 8);
		}
		target_h = area_h[m].center;
		circle(src, target_h, 1, Scalar(0, 0, 255), 1, 8);
		putText(src, "H", verct[0], FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
	}
	for (size_t m = 0; m < area_bore.size(); m++) {
		target_bore = area_bore[m].center;
	}
}

void position::analyse_B(Mat& src)
{
	int sure_number = -1;
	for (int i = 0; i < rect_roi.size(); i++) {
		init_B();
		Mat srcImage = src(rect_roi[i]);
		B_detection(srcImage,src);
		if (condition1&&condition2&&condition3&&condition4)
			sure_number = i;
		else {
			Mat srcCopy = Mat(srcImage.rows, srcImage.cols, srcImage.depth());
			transpose(srcImage, srcCopy);
			flip(srcCopy, srcCopy, 0);  //rotate 90 
			init_B();
			B_detection(srcCopy,src);
			if (condition1&&condition2&&condition3&&condition4)
				sure_number = i;
		}
	}
	if (sure_number >= 0) {
		show_B = true;
		target_b = rect_center(rect_roi[sure_number]);
		rectangle(src, rect_roi[sure_number], Scalar(0, 255, 0), 1, 8);
		circle(src, target_b, 1, Scalar(0, 0, 255), 1, 8);
		putText(src, "B", rect_roi[sure_number].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
	}
	imshow("src", src);
	waitKey(0);
}
bool position::find_ratio(vector<float> k_ratio) {
	bool same = false;
	for (size_t i = 0; i < k_ratio.size(); i++) {
		for (size_t j = i + 1; j < k_ratio.size(); j++) {
			if (fabs(k_ratio[i] - k_ratio[j]) < 0.15)
			{
				same = true; sure_i = i + 1; sure_j = j + 1;
			}
		}
	}
	return same;
}
float position::ratio_calculate(Point2f a, Point2f b) {
	float ratio;
	if (fabs(a.x - b.x) < 1e-6) {
		ratio = 99999;
	}
	else ratio = (a.y - b.y) / (a.x - b.x);
	return ratio;
}
void position::change_corners(int a, int b, vector<Point2f>& corners) {
	swap(corners[a], corners[b]);
}
void position::judging_condition(Mat src) {
	condition1 = true;
	float ratio_one = ratio_calculate(corners[0], corners[sure_i]);
	float ratio_two;
	int m = 0, n = 0;

	/*找出上三点中间的点*/
	Point2f middle_point;
	middle_point = (corners[0] + corners[sure_i] + corners[sure_j]) / 3;

	for (size_t i = 1; i < corners.size(); i++) {
		if (i != sure_i && i != sure_j)
		{
			n = m;
			m = i;
		}
	}
	ratio_two = ratio_calculate(corners[m], corners[n]);
	if (fabs(ratio_one - ratio_two) < 0.15)
		condition2 = true;

	/*cout << "distance：" << endl;
	cout << ":::::::::::::::::::::::::" << endl;
	cout << distance_b(middle_point, corners[m]) << endl;
	cout << distance_b(middle_point, corners[n]) << endl;
	cout << ":::::::::::::::::::::::::" << endl;
	cout << condition4 << endl;*/
	if (fabs(distance_b(middle_point, corners[m]) - distance_b(middle_point, corners[n])) < 3)
		condition4 = true;

	if (middle_point == corners[0])
	{
		if (distance_compare(middle_point, corners[sure_i], corners[m], corners[n]))
			condition3 = true;
	}
	else
	{
		if (distance_compare(middle_point, corners[0], corners[m], corners[n]))
			condition3 = true;
	}
	/*Mat rre;
	src.copyTo(rre);
	circle(rre, corners[m], 2, Scalar(0, 0, 0), 2, 8, 0);
	circle(rre, corners[n], 2, Scalar(255, 255, 0), 2, 8, 0);
	circle(rre, middle_point, 2, Scalar(255, 0, 0), 2, 8, 0);
	circle(rre, corners[sure_i], 2, Scalar(255, 0, 255), 2, 8, 0);
	circle(rre, corners[sure_j], 2, Scalar(0, 0, 255), 2, 8, 0);*/
	/*imshow("rre", rre);
	waitKey(1);*/
}
void position::filled_ratio() {
	k_ratio.push_back(ratio_calculate(corners[0], corners[1]));
	k_ratio.push_back(ratio_calculate(corners[0], corners[2]));
	k_ratio.push_back(ratio_calculate(corners[0], corners[3]));
	k_ratio.push_back(ratio_calculate(corners[0], corners[4]));
}
bool y_poll(Point2f aa,Point2f bb) {
	return (aa.y<bb.y);
}
void position::B_detection(Mat srcImage,Mat src) {
	int maxCorners = 10;
	int maxTrackbar = 100;
	if (maxCorners < 1) { maxCorners = 1; }

	//初始化 Shi-Tomasi algorithm的一些参数
	double qualityLevel = 0.05;
	double minDistance = 70;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	Mat src_gray;
	// 角点检测
	//cvtColor(srcImage, src_gray, CV_RGB2GRAY);
	goodFeaturesToTrack(srcImage, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
	TermCriteria criteria = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 40, 0.01);

	//亚像素检测
	/*cornerSubPix(src_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);*/
	//画出检测到的角点
	if(/*corners.size()==5*/1){		
		int r = 4;
		sort(corners.begin(), corners.end(), y_poll);
		for (int i = 0; i < corners.size(); i++)
		{
			cout << i << ":" << corners[i] << endl;
			circle(src, corners[i], r, Scalar(255, 0, 0), -1, 8, 0);
		}
		vector<float>y_level;
		for (int j = 0; j < corners.size(); j++) {
			if (y_level.size()==0) {
				y_level.push_back(corners[j].y);
			}
			else {
				if (fabs(y_level[y_level.size()- 1] - corners[j].y) > 50)
					y_level.push_back(corners[j].y);
			}
		}
		for (int w = 0; w < y_level.size(); w++) {
			cout <<"Point"<< y_level[w] << endl;
			line(src, Point(100, y_level[w]), Point(900, y_level[w]), Scalar(0, 0, 255), 5, 8);
		}
		/*filled_ratio();
		if (find_ratio(k_ratio)) {
			judging_condition(srcImage);
		}
		else {
			change_corners(0, 1, corners);
			k_ratio.clear();
			filled_ratio();
			if (find_ratio(k_ratio))
				judging_condition(srcImage);
			else {
				change_corners(0, 2, corners);
				k_ratio.clear();
				filled_ratio();
				if (find_ratio(k_ratio))
					judging_condition(srcImage);
			}
		}*/


		cout << "条件：" << endl;
		cout << "*************************" << endl;
		cout << condition1 << endl;
		cout << condition2 << endl;
		cout << condition3 << endl;
		cout << condition4 << endl;
		cout << sure_i << endl;
		cout << sure_j << endl;
		cout << "*************************" << endl;
		namedWindow("角点检测", CV_WINDOW_NORMAL);
		imshow("角点检测", srcImage);
		namedWindow("src", CV_WINDOW_NORMAL);
		imshow("src", src);
		waitKey(0);
	}
}


Point2f position::rect_center(Rect a) {
	return ((a.tl() + a.br()) / 2);
}


bool position::isPointInRect(Point P, Rect rect) {

	Point A = rect.tl();
	Point B(rect.tl().x + rect.width, rect.tl().y);
	Point C(rect.tl().x + rect.width, rect.tl().y + rect.height);
	Point D(rect.tl().x, rect.tl().y + rect.height);
	int x = P.x;
	int y = P.y;
	int a = (B.x - A.x)*(y - A.y) - (B.y - A.y)*(x - A.x);
	int b = (C.x - B.x)*(y - B.y) - (C.y - B.y)*(x - B.x);
	int c = (D.x - C.x)*(y - C.y) - (D.y - C.y)*(x - C.x);
	int d = (A.x - D.x)*(y - D.y) - (A.y - D.y)*(x - D.x);
	if ((a >= 0 && b >= 0 && c >= 0 && d >= 0) || (a <= 0 && b <= 0 && c <= 0 && d <= 0)) {
		return true;
	}

	//      AB X AP = (b.x - a.x, b.y - a.y) x (p.x - a.x, p.y - a.y) = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
	//      BC X BP = (c.x - b.x, c.y - b.y) x (p.x - b.x, p.y - b.y) = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x);
	return false;
}

float position::distance_b(Point2f a, Point2f b) {
	return(sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)));
}

bool position::distance_compare(Point2f a, Point2f b, Point2f c, Point2f d) {

	float distance1 = distance_b(a, b);
	float distance2 = distance_b(c, d);
	float accuracy = 0.5;
	if (fabs(distance1 - distance2) < 5)
		return true;
	else return false;
}

void position::init_B() {
	corners.clear();
	k_ratio.clear();
	condition1 = false;
	condition2 = false;
	condition3 = false;
	condition4 = false;
}

void position::analyse_C(Mat& src)
{
	int sure_number = -1;
	for (int i = 0; i < rect_roi.size(); i++) {
		bool condition_one = false;
		bool condition_two = false;
		bool condition_three = false;
		Mat src_c, dst;
		/*Rect sense = dilate_rect(rect_roi[i],src);*/
		src(rect_roi[i]).copyTo(src_c);
		src(rect_roi[i]).copyTo(dst);
		medianBlur(src_c, src_c, 3);
		cvtColor(src_c, src_c, CV_BGR2GRAY);

		vector<Vec3f> c_pcircle;
		HoughCircles(src_c, c_pcircle, CV_HOUGH_GRADIENT, 1, 20, 100, 15, 5, 20);

		for (size_t m = 0; m < c_pcircle.size(); m++) {
			Vec3f  mcm = c_pcircle[m];
			circle(dst, Point(mcm[0], mcm[1]), mcm[2], Scalar(0, 0, 255), 1, LINE_AA);
			circle(dst, Point(mcm[0], mcm[1]), 2, Scalar(198, 23, 255), 2, LINE_AA);
		}
		vector<Point2f> ccs;//霍夫圆圆心
		vector<float> radius;//霍夫圆半径

		for (size_t t = 0; t < c_pcircle.size(); t++) {
			Vec3f  mcm = c_pcircle[t];
			ccs.push_back(Point(mcm[0], mcm[1]));
			radius.push_back(mcm[2]);
		}
		imshow("C区霍夫", dst);
		waitKey(0);
		int real;

		Point2f c_center = (rect_roi[i].br() - rect_roi[i].tl()) / 2;
		for (size_t m = 0; m < radius.size(); m++) {
			for (size_t n = m + 1; n < radius.size(); n++) {
				if (fabs(distance_b(c_center, ccs[m]) - distance_b(c_center, ccs[n])) < 4.0&&distance_b(c_center, ccs[m]) > 0)
					condition_two = true;


				float ee = distance_b(ccs[m], ccs[n]);
				float ss = distance_b(c_center, ccs[m]);
				float mm = distance_b(c_center, ccs[n]);
				float cos_ratio = (ss*ss + mm * mm - ee * ee) / (2 * ss*mm);
				if (-0.5 < cos_ratio < 0.866)
					condition_one = true;
				/*cout << "cos:" << cos_ratio << endl;*/
			}
		}
		/*cout << "C区:" << endl;
		cout << condition_one << endl;
		cout << condition_two << endl;
		cout << condition_three << endl;
		cout << "~~~~~~~~~~~~~~" << endl;*/

		if (condition_one&&condition_two)
		{
			sure_number = i;
		}
		 
	}
	if (sure_number >= 0) {
		show_C = true;
		target_c = rect_center(rect_roi[sure_number]);
		rectangle(src, rect_roi[sure_number], Scalar(0, 255, 0), 2, 8);
		circle(src, target_c, 1, Scalar(0, 0, 255), 1, 8);
		putText(src, "C", rect_roi[sure_number].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
	}
}




void position::B_svm_analyse(Mat src) {
	int threshold_min = 80;
	Mat srcImage;
	for (int i = 0; i < rect_roi.size(); i++) {
		src(rect_roi[i]).copyTo(srcImage);
		Mat blur_src;
		Mat gray_src;
		vector<vector<Point>> map_contours;
		vector<vector<Point>> map_all_contours;
		vector<Vec4i> hierarchy;
		/*模糊*/
		GaussianBlur(srcImage, blur_src, Size(3, 3), 0, 0);
		medianBlur(blur_src, blur_src, 3);
		cvtColor(blur_src, gray_src, CV_RGB2GRAY);
		Canny(gray_src, gray_src, threshold_min, threshold_min * 3, 3, false);
		//findContours(gray_src, map_contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		findContours(gray_src, map_all_contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);
		Mat w_mat = Mat::zeros(srcImage.size(), srcImage.type());
		for (size_t i = 0; i < map_all_contours.size(); i++)
		{
			drawContours(w_mat, map_all_contours, i, Scalar(255, 255, 255), 1, 8);
		}
		circle(w_mat, Point(w_mat.cols / 2, w_mat.rows / 2), w_mat.cols / 2+1, Scalar(0, 0, 0), 3, 8);
		imshow("w_mat", w_mat);
		waitKey(0);
		compare = -1;
		fill_extra(w_mat);
		if (compare > 0) {
			show_B = true;
			target_b = rect_center(rect_roi[i]);
			rectangle(src, rect_roi[i], Scalar(0, 255, 0), 2, 8);
			circle(src, target_b, 1, Scalar(0, 0, 255), 1, 8);
			putText(src, "B", rect_roi[i].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8);
		}
	}
}

void position::fill_extra(Mat src) {
	/*vector<vector<Point>> contours;
	Mat src_gray;
	Canny(src, src_gray, 10, 250, 3, false);
	findContours(src_gray, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat dst = Mat::zeros(src.size(), src.type());
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(dst, contours, i, Scalar(255, 255, 255), CV_FILLED, 8);
	}
	imshow("1",dst);
	waitKey(0);*/
	Mat kernel1 = getStructuringElement(MORPH_ELLIPSE, Size(1, 1));
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat kernel3 = getStructuringElement(MORPH_RECT, Size(3, 3));

	////cvtColor(dst,dst, CV_RGB2GRAY);
	dilate(src, src, kernel2);
	erode(src, src, kernel1);
	/*medianBlur(dst, dst, 3);
	erode(dst, dst, kernel3);
	 */
	Point2f character;
	character = ann_b(src);
	if (/*character.x == 11&&*/ character.y > 60.0) {
		message_character = character;
		compare = 1;
	}
	imshow("w", src);
	//imshow("2", dst);
	waitKey(0);
}
Point2f position::ann_b(Mat src) {
	//string dirNum[26] = { "A", "B", "C", "D", "E", "F", "G", "H","I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	//std::string dirNum[24] = { "0", "15", "30", "45", "60", "75", "90", "105","120", "135", "150", "165", "180", "195", "210", "225", "240", "255", "270", "285", "300", "315", "330", "345" };
	std::string dirNum[12] = { "0", "30", "60", "90", "120", "150", "180", "210","240", "270", "300", "330"};
	Ptr<ANN_MLP> model = StatModel::load<ANN_MLP>("w_English.xml");
	Mat srcImage = src;
	resize(srcImage, srcImage, Size(30, 30), (0, 0), (0, 0), INTER_AREA);
	/*cvtColor(srcImage, srcImage, CV_BGR2GRAY);
	threshold(srcImage, srcImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);*/
	srcImage.convertTo(srcImage, CV_8UC1);
	Mat_<float> testMat(1, 30 * 30);
	for (int i = 0; i < 30 * 30; i++) {
		if (i >= 30 * 30 || i < 0) { cout << "vetcor下标越界" << endl; break; }
		testMat.at<float>(0, i) = (float)srcImage.at<uchar>(i / 30, i % 30);
	}

	//使用训练好的MLP model预测测试图像
	Mat dst;
	model->predict(testMat, dst);
	/*std::cout << "testMat: \n" << testMat << "\n" << std::endl;
	std::cout << "dst: \n" << dst << "\n" << std::endl;*/
	double maxVal = 0;
	Point maxLoc;
	minMaxLoc(dst, NULL, &maxVal, NULL, &maxLoc);
	std::cout << " 测试结果：" << dirNum[maxLoc.x] << "置信度:" << maxVal * 100 << "%" << std::endl;

	Point2f chara;
	float x = maxLoc.x;
	float y = maxVal * 100;
	chara.x = x;
	chara.y = y;
	return chara;
}
Point2f position::svm_b(Mat src) {
	std::string dirNum[24] = { "0", "15", "30", "45", "60", "75", "90", "105","120", "135", "150", "165", "180", "195", "210", "225", "240", "255", "270", "285", "300", "315", "330", "345" };
	Ptr<SVM> model = StatModel::load<SVM>("w_b.xml");


	Mat srcImage = src;
	 
	/*cvtColor(srcImage, srcImage, CV_BGR2GRAY);
	threshold(srcImage, srcImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(srcImage, srcImage, kernel);*/
	srcImage.convertTo(srcImage, CV_32FC1);
	resize(srcImage, srcImage, Size(30, 30), (0, 0), (0, 0), INTER_AREA);
	Mat_<float> testMat(1, 30 * 30);
	srcImage = srcImage.reshape(1, 1);
	/*for (int i = 0; i < 30 * 30; i++) {
		if (i >= 30 * 30 || i < 0) { cout << "vetcor下标越界" << endl; break; }
		testMat.at<float>(0, i) = (float)srcImage.at<uchar>(i / 30, i % 30);
	}*/


	 



	//使用训练好的MLP model预测测试图像
	 
	int m=model->predict(testMat);
	//std::cout << "testMat: \n" << testMat << "\n" << std::endl;
	//std::cout << "dst: \n" << dst << "\n" << std::endl;
	/*double maxVal = 0;
	Point maxLoc;
	minMaxLoc(dst, NULL, &maxVal, NULL, &maxLoc);
	std::cout << " 测试结果：" << dirNum[maxLoc.x] << "置信度:" << maxVal * 100 << "%" << std::endl;
	Point2f chara;
	float x = maxLoc.x;
	float y = maxVal * 100;
	chara.x = x;
	chara.y = y;
	return chara;*/
	cout << dirNum[m] << endl;
	Point2f chara;
	float x = 0;
	float y =0;
	chara.x = x;
	chara.y = y;
	return chara;
}

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
		/*imshow("圆检测", srcImage);
		waitKey(0);*/
		if (A_concentric(roi_ccs, roi_radius)) {
			sure_number = k;
		}
	}
	if (sure_number >= 0) {
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
	else {
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
	if (fabs(a.x - b.x) < accuracy&&fabs(a.y - b.y < accuracy))
		return 1;
	else return 0;
}