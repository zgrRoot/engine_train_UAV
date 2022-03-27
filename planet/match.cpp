#include"fly.h"


/*模板匹配函数*/
void position::Match_imge(cv::Mat& src, cv::Mat& temp, Point& temLoc) {
	 
	if (!temp.data)
	{
		cout << "temp图像读取失败！！\n" << endl;
	}
	 
	diate_image(temp);
	imshow("temp", temp);
	 
	waitKey(0);
	int width = src.cols - temp.cols + 1;
	int height = src.rows - temp.rows + 1;
	Mat result(width, height, CV_32FC1);

	matchTemplate(src, temp, result, CV_TM_SQDIFF, Mat());
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	Point minLoc;
	Point maxLoc;
	double min, max;
	minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
	temLoc = minLoc;
	
	 
	 
}
 


/*从备选的ROI区域中找出锁定区域B区域*/
void position::roi_match_b(Point temLoc_b, cv::Mat temp_b, Point2f target_b,Mat& src) {
	Rect rect1 = Rect(temLoc_b.x, temLoc_b.y, temp_b.cols, temp_b.rows);
	int max_number = 0;
	float max_area_coincide = 0;
	float present_coincide;
	for (int i = 0; i < rect_roi.size(); i++) {
		Rect rect2 = rect_roi[i];
		Rect rect3 = rect1 & rect2;

		present_coincide = rect3.area();
		if (present_coincide > max_area_coincide)
		{
			max_number = i;
			max_area_coincide = present_coincide;
		}
	}
	Rect target_roi = rect_roi[max_number];


	target_b = Point2f((target_roi.tl().x + target_roi.br().x) / 2, (target_roi.tl().y + target_roi.br().y) / 2);
	circle(src, target_b, 1, Scalar(255, 0, 255), 3, 8);
	cout << "B区:" << endl;
	cout << target_b << endl;
	solve_diretion(target_b, src);
}


/*从备选的ROI区域中找出锁定区域H区域*/
void position::roi_match_h(Point temLoc_h, cv::Mat temp_h, Point2f target_h, Mat& src) {
	Rect rect1 = Rect(temLoc_h.x, temLoc_h.y, temp_h.cols, temp_h.rows);
	int max_number = 0;
	float max_area_coincide = 0;
	float present_coincide;
	for (int i = 0; i < rect_roi.size(); i++) {
		Rect rect2 = rect_roi[i];
		Rect rect3 = rect1 & rect2;

		present_coincide = rect3.area();
		if (present_coincide > max_area_coincide)
		{
			max_number = i;
			max_area_coincide = present_coincide;
		}
	}
	Rect target_roi = rect_roi[max_number];


	target_h = Point2f((target_roi.tl().x + target_roi.br().x) / 2, (target_roi.tl().y + target_roi.br().y) / 2);
	circle(src, target_h, 1, Scalar(255, 0, 255), 3, 8);
	cout << "H区:" << endl;
	cout << target_h << endl;
	solve_diretion(target_h, src);
}

void position::roi_match_c(Point temLoc_c, cv::Mat temp_c, Point2f target_c, Mat& src) {
	Rect rect1 = Rect(temLoc_c.x, temLoc_c.y, temp_c.cols, temp_c.rows);
	int max_number = 0;
	float max_area_coincide = 0;
	float present_coincide;
	for (int i = 0; i < rect_roi.size(); i++) {
		Rect rect2 = rect_roi[i];
		Rect rect3 = rect1 & rect2;

		present_coincide = rect3.area();
		if (present_coincide > max_area_coincide)
		{
			max_number = i;
			max_area_coincide = present_coincide;
		}
	}
	Rect target_roi = rect_roi[max_number];


	target_c = Point2f((target_roi.tl().x + target_roi.br().x) / 2, (target_roi.tl().y + target_roi.br().y) / 2);
	circle(src, target_c, 1, Scalar(255, 0, 255), 3, 8);
	cout << "C区:" << endl;
	cout << target_c << endl;
	solve_diretion(target_c, src);



}





void position::diate_image(Mat& roi) {
	Mat blur_roi, gray_roi;
	 
	medianBlur(roi, blur_roi, 1);

	cvtColor(blur_roi, gray_roi, CV_RGB2GRAY);
	Canny(gray_roi, gray_roi, 80, 240, 3, false);
	vector<vector<Point>>roi_contours;
	findContours(gray_roi, roi_contours,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	Mat dst = Mat::zeros(roi.size(), roi.type());
	for (size_t i = 0; i < roi_contours.size(); i++) {
		drawContours(dst, roi_contours, i, Scalar(255, 255, 255));
	};
	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(1, 1));
	dilate(dst, dst, kernel1);
	erode(dst, dst, kernel2);
	dst.copyTo(roi);
}


void position::ann_HA(Mat& src) {
	std::string dirNum[26] = { "A", "B", "C","H"};
	Ptr<ANN_MLP> model = StatModel::load<ANN_MLP>("src.xml");

	for (int i=0; i < rect_roi.size(); i++) {
		Mat srcImage = src(rect_roi[i]);
		resize(srcImage, srcImage, Size(30, 30), (0, 0), (0, 0), INTER_AREA);
		cvtColor(srcImage, srcImage, CV_BGR2GRAY);
		threshold(srcImage, srcImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(srcImage, srcImage, kernel);
		srcImage.convertTo(srcImage, CV_8UC1);
		Mat_<float> testMat(1, 30*30);
		for (int i = 0; i < 30*30; i++) {
			if (i >= 30 * 30 || i < 0) { cout << "vetcor下标越界" << endl; break; }
			testMat.at<float>(0, i) = (float)srcImage.at<uchar>(i / 30, i % 30);
		}
		
	    //使用训练好的MLP model预测测试图像
		Mat dst;
		model->predict(testMat, dst);
		//std::cout << "testMat: \n" << testMat << "\n" << std::endl;
		//std::cout << "dst: \n" << dst << "\n" << std::endl;
		double maxVal = 0;
		Point maxLoc;
		minMaxLoc(dst, NULL, &maxVal, NULL, &maxLoc);
		std::cout<<" 测试结果：" << dirNum[maxLoc.x] << "置信度:" << maxVal * 100 << "%" << std::endl;
		putText(src, dirNum[maxLoc.x], rect_roi[i].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 0), 1, 8);
	}
}

void position::svm_HA(Mat& src) {
	std::string dirNum[1] = { "H" };
	Ptr<SVM> model = StatModel::load<SVM>("W.xml");

	for (int i = 0; i < rect_roi.size(); i++) {
		Mat srcImage = src(rect_roi[i]);
		resize(srcImage, srcImage, Size(30, 30), (0, 0), (0, 0), INTER_AREA);
		/*cvtColor(srcImage, srcImage, CV_BGR2GRAY);
		threshold(srcImage, srcImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(srcImage, srcImage, kernel);*/
		srcImage.convertTo(srcImage, CV_8UC1);
		Mat_<float> testMat(1, 30 * 30);
		for (int i = 0; i < 30 * 30; i++) {
			if (i >= 30 * 30 || i < 0) { cout << "vetcor下标越界" << endl; break; }
			testMat.at<float>(0, i) = (float)srcImage.at<uchar>(i / 30, i % 30);
		}

		//使用训练好的MLP model预测测试图像
		Mat dst;
		model->predict(testMat, dst);
		//std::cout << "testMat: \n" << testMat << "\n" << std::endl;
		//std::cout << "dst: \n" << dst << "\n" << std::endl;
		double maxVal = 0;
		Point maxLoc;
		minMaxLoc(dst, NULL, &maxVal, NULL, &maxLoc);
		std::cout << " 测试结果：" << dirNum[maxLoc.x] << "置信度:" << maxVal * 100 << "%" << std::endl;
		putText(src, dirNum[maxLoc.x], rect_roi[i].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 0), 1, 8);
	}
}

	 
	 