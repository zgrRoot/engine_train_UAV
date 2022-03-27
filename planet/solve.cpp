#include"fly.h"

void position::solve_diretion(Point2f& target,cv::Mat src) {
	Point2f center_point = Point2f(src.cols / 2,src.rows / 2);
	Point2f turn_target;
	turn_target.x = target_c.x-center_point.x;
	turn_target.y = target_c.y - center_point.y;
	if (turn_target.x > 0)
	{
		cout << "向右运动\n" << endl;
		right = true;
	}
	if (turn_target.x < 0) {
		cout << "向左运动\n" << endl;
		left = true;
	}
	if (turn_target.y < 0) {
		cout << "向上运动\n" << endl;
		front = true;
	}
	if (turn_target.y > 0) {
		cout << "向下运动\n" << endl;
		back = true;
	}
	if (turn_target.x ==0 && turn_target.y ==0) {
		down= true;
		cout << "不必移动" << endl;
	}

}

void position::order_can() {
	if (up) order | (1 << 5);
	if (down) order | (1 << 4);
	if (front) order | (1 << 3);
	if (back) order | (1 << 2);
	if (left) order | (1 << 1);
	if (right) order | (1);
}

void position::roi_cut(Mat& src) {
	rect_roi.clear();
	int threshold_min = 80;

	Mat srcImage;
	src.copyTo(srcImage);

	Mat blur_src;
	Mat gray_src;
	vector<vector<Point>> map_contours;
	vector<vector<Point>> map_all_contours;

	/*模糊*/
	GaussianBlur(srcImage, blur_src, Size(3, 3), 0, 0);
	medianBlur(blur_src, blur_src, 3);


	cvtColor(blur_src, gray_src, CV_RGB2GRAY);
	Canny(gray_src, gray_src, threshold_min, threshold_min * 3, 3, false);
	findContours(gray_src, map_contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	findContours(gray_src, map_all_contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);

	Mat contour_mat = Mat::zeros(src.size(), src.type());
	for (size_t i = 0; i < map_contours.size(); i++)
	{
		drawContours(contour_mat, map_contours, i, Scalar(255, 255, 255), 1, 8);
	}
	imshow("contour_mat", contour_mat);

	vector<vector<Point>> ploy_contours(map_contours.size());
	vector<RotatedRect>  rect_contours(map_contours.size());
	vector<Point2f> ccs(map_contours.size());
	vector<float> radius(map_contours.size());

	for (size_t i = 0; i < map_contours.size(); i++) {
		approxPolyDP(Mat(map_contours[i]), ploy_contours[i], 3, true);

		minEnclosingCircle(ploy_contours[i], ccs[i], radius[i]);
		rect_contours[i] = minAreaRect(ploy_contours[i]);
		rect_roi.push_back(boundingRect(ploy_contours[i]));
	}



	/*ROI区域裁剪*/

	sort(rect_roi.begin(), rect_roi.end(), roi_sort);
	Rect max_rect = rect_roi.back();
	float max_area = max_rect.area();
	vector<Rect>::iterator it;
	for (it = rect_roi.begin(); it != rect_roi.end();) {
		Rect res = *it;
		if (max_area / res.area() > 3)
			it = rect_roi.erase(it);
		else
			++it;
	}
	for (int t = 0; t < rect_roi.size(); t++) {
		/*rectangle(src, rect_roi[t], Scalar(0, 0, 255), 1, 8);*/
		Mat srcImage = src(rect_roi[t]);
		GaussianBlur(srcImage, blur_src, Size(3, 3), 0, 0);
		medianBlur(blur_src, blur_src, 3);
		cvtColor(blur_src, gray_src, CV_RGB2GRAY);
		Canny(gray_src, gray_src, threshold_min, threshold_min * 3, 3, false);
		findContours(gray_src, map_contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		findContours(gray_src, map_all_contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);
		Mat w_mat = Mat::zeros(srcImage.size(), srcImage.type());
		for (size_t i = 0; i < map_all_contours.size(); i++)
		{
			drawContours(w_mat, map_all_contours, i, Scalar(255, 255, 255), 3, 8);
		}
		//erode(dst, dst, kernel3);

		//resize(dst, dst, Size(30, 30));
		imshow("roi", w_mat);
		waitKey(0);
	}
}
/*ROI区域面积排序*/
bool position::roi_sort(const Rect& a, const Rect& b)
{
	return a.area() < b.area();//升序
}

float position::distance_capture(Rect H_rect,Mat&src) {
			// 计算成像宽/高
			double width = H_rect.width * UNIT_PIXEL_W;
			double height = H_rect.height * UNIT_PIXEL_H;
			// 分别以宽/高为标准计算距离
			double distanceW = w * f / width;
			double distanceH = h * f / height;

			char disW[50], disH[50];
			sprintf_s(disW, "DistanceW : %.2fcm", distanceW);
			sprintf_s(disH, "DistanceH : %.2fcm", distanceH);
			cv::putText(src, disW,target_h, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 255, 0), 1, 8);
			cv::putText(src, disH, target_h, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 255, 0), 1, 8);
			return distanceW;

}