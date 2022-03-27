#pragma once
#ifndef FLY_H
#define FLY_H
#include<opencv2/opencv.hpp>
#include<iostream>
#include <opencv2\ml.hpp>
#include <opencv2/cvconfig.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <io.h>

using namespace cv;
using namespace std;
using namespace ml;

# define UNIT_PIXEL_W 0.0000048
# define UNIT_PIXEL_H 0.0000048

const double f = 6.0;  // 焦距
const double w = 600.0;   // 被测物体宽度
const double h = 600.0;   // 被测物体高度

class position {
public:
	//position();//构造函数
	//~position();//析构函数
	void run(cv::Mat& src);
	/*B区识别条件*/
	bool condition1 = false;
	bool condition2 = false;
	bool condition3 = false;
	bool condition4 = false;
	/*ABCH区域是否甄别*/
	bool show_A=false;
	bool show_B = false;
	bool show_C = false;
	bool show_H = false;
	 
 
private:
	Mat temp_b= imread("C:\\Users\\Lenovo\\Pictures\\w_demo.jpg.png");//B区模板
	Mat temp_h=imread("C:\\Users\\Lenovo\\Pictures\\H.png");//H区模板
	Mat temp_c = imread("C:\\Users\\Lenovo\\Pictures\\C.jpg");//C区模板

	Mat b_roi;//B区roi
	Mat a_roi;//A区roi
	Mat h_roi;//H区roi
	Mat handle_src;//预处理后的src

	Point2f target_b;//B区降落点
	Point2f target_a;//A区降落点
	Point2f target_h;//H区降落点
	Point2f target_c;//C区降落点
	 

	Point temLoc_b;//模板匹配后的返回点 B区
	Point temLoc_h;//模板匹配后的返回点 H区
	Point temLoc_c;//模板匹配后的返回点 C区

	/*无人机运动指令*/
	bool up = false;
	bool down = false;
	bool front = false;
	bool back = false;
	bool left = false;
	bool right = false;
	int order=0;//向串口传输的运动数据

	int sure_i, sure_j;//B区甄别点
	vector<Point2f> corners;//B区甄别点容器
	vector<float> k_ratio;//B区识别斜率
	vector<Rect> rect_roi;//剪裁出的ROI区域
	vector<int>  circle_count;//roi区域同心圆数量

	void Match_imge(cv::Mat& src, cv::Mat& temp, Point& temLoc);//模板匹配函数
	void roi_match_b(Point temLoc_b, cv::Mat temp_b, Point2f target_b,Mat& src);//从备选的ROI区域中找出锁定区域B区
	void roi_match_h(Point temLoc_h, cv::Mat temp_h, Point2f target_h, Mat& src);//从备选的ROI区域中找出锁定区域B区
	void roi_match_c(Point temLoc_c, cv::Mat temp_c, Point2f target_c, Mat& src);//从备选的ROI区域中找出锁定区域C区
	void solve_diretion(Point2f& target_c,cv::Mat src);//根据识别出的降落点确定运动方向
	
	void A_analyse(Mat& src);//A区查找
	 
	void B_analyse(Mat& src);//B区查找
	void C_analyse(Mat& src);//C区查找
	void H_analyse(Mat& src);//H区查找
	void handle_image(Mat& srImage); //图像预处理
	void diate_image(Mat& roi);//对匹配模板和roi区域进行预处理
	void svm_HA(Mat& src);//H区A区SVM
	void ann_HA(Mat& src);//H区A区ANN


	 /*传统识别部分*/
	void preprocessing(Mat& src);//图像预处理函数
	void analyse_H(Mat& src);//H区识别
	void analyse_B(Mat& src);//B区识别
	void analyse_C(Mat& src);//C区识别

	//Rect dilate_rect(Rect a);//将矩形区域适量扩大
	Point2f rect_center(Rect i);//计算矩形roi的中心
 
	int point_compare(Point2f a, Point2f b);//比较两个点是否相近
	static bool roi_sort(const Rect& a, const Rect& b);//roi区域面积排序
	bool isPointInRect(Point P, Rect rect);//判断点是否在Rect内
	bool find_ratio(vector<float> k_ratio);//检索出四个斜率中相等的两个
	bool A_concentric(vector<Point2f>ccs, vector<float>radius);//A区同心圆数据筛选
	bool distance_compare(Point2f a,Point2f b,Point2f c,Point2f d);//比较两条线段是否长度相近
	float ratio_calculate(Point2f a, Point2f b);//计算斜率
	float distance_b(Point2f a, Point2f b);//计算距离函数
	void change_corners(int a, int b, vector<Point2f>& corners);//交换容器内元素
	void judging_condition(Mat src);//三个判断条件验证
	void filled_ratio();//向容器中填入4组斜率
	void order_can();//将获得的运动数据成order
	void roi_cut(Mat& src);//ROI区域裁剪
	void init_B();//B区初始化
	float distance_capture(Rect H_rect,Mat& src);
	void B_detection(Mat src);//B区检测函数整合
	void fill_extra(Mat src);//从B区roi中提取W
	Point2f ann_b(Mat src);//B区svm识别W
	void B_svm_analyse(Mat srcImage);//B区识别
	Point2f message_character;
	int compare = -1;

};

 
 
  
 


#endif // !FLY_H
