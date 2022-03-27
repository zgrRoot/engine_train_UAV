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

const double f = 6.0;  // ����
const double w = 600.0;   // ����������
const double h = 600.0;   // ��������߶�

class position {
public:
	//position();//���캯��
	//~position();//��������
	void run(cv::Mat& src);
	/*B��ʶ������*/
	bool condition1 = false;
	bool condition2 = false;
	bool condition3 = false;
	bool condition4 = false;
	/*ABCH�����Ƿ����*/
	bool show_A=false;
	bool show_B = false;
	bool show_C = false;
	bool show_H = false;
	 
 
private:
	Mat temp_b= imread("C:\\Users\\Lenovo\\Pictures\\w_demo.jpg.png");//B��ģ��
	Mat temp_h=imread("C:\\Users\\Lenovo\\Pictures\\H.png");//H��ģ��
	Mat temp_c = imread("C:\\Users\\Lenovo\\Pictures\\C.jpg");//C��ģ��

	Mat b_roi;//B��roi
	Mat a_roi;//A��roi
	Mat h_roi;//H��roi
	Mat handle_src;//Ԥ������src

	Point2f target_b;//B�������
	Point2f target_a;//A�������
	Point2f target_h;//H�������
	Point2f target_c;//C�������
	 

	Point temLoc_b;//ģ��ƥ���ķ��ص� B��
	Point temLoc_h;//ģ��ƥ���ķ��ص� H��
	Point temLoc_c;//ģ��ƥ���ķ��ص� C��

	/*���˻��˶�ָ��*/
	bool up = false;
	bool down = false;
	bool front = false;
	bool back = false;
	bool left = false;
	bool right = false;
	int order=0;//�򴮿ڴ�����˶�����

	int sure_i, sure_j;//B������
	vector<Point2f> corners;//B����������
	vector<float> k_ratio;//B��ʶ��б��
	vector<Rect> rect_roi;//���ó���ROI����
	vector<int>  circle_count;//roi����ͬ��Բ����

	void Match_imge(cv::Mat& src, cv::Mat& temp, Point& temLoc);//ģ��ƥ�亯��
	void roi_match_b(Point temLoc_b, cv::Mat temp_b, Point2f target_b,Mat& src);//�ӱ�ѡ��ROI�������ҳ���������B��
	void roi_match_h(Point temLoc_h, cv::Mat temp_h, Point2f target_h, Mat& src);//�ӱ�ѡ��ROI�������ҳ���������B��
	void roi_match_c(Point temLoc_c, cv::Mat temp_c, Point2f target_c, Mat& src);//�ӱ�ѡ��ROI�������ҳ���������C��
	void solve_diretion(Point2f& target_c,cv::Mat src);//����ʶ����Ľ����ȷ���˶�����
	
	void A_analyse(Mat& src);//A������
	 
	void B_analyse(Mat& src);//B������
	void C_analyse(Mat& src);//C������
	void H_analyse(Mat& src);//H������
	void handle_image(Mat& srImage); //ͼ��Ԥ����
	void diate_image(Mat& roi);//��ƥ��ģ���roi�������Ԥ����
	void svm_HA(Mat& src);//H��A��SVM
	void ann_HA(Mat& src);//H��A��ANN


	 /*��ͳʶ�𲿷�*/
	void preprocessing(Mat& src);//ͼ��Ԥ������
	void analyse_H(Mat& src);//H��ʶ��
	void analyse_B(Mat& src);//B��ʶ��
	void analyse_C(Mat& src);//C��ʶ��

	//Rect dilate_rect(Rect a);//������������������
	Point2f rect_center(Rect i);//�������roi������
 
	int point_compare(Point2f a, Point2f b);//�Ƚ��������Ƿ����
	static bool roi_sort(const Rect& a, const Rect& b);//roi�����������
	bool isPointInRect(Point P, Rect rect);//�жϵ��Ƿ���Rect��
	bool find_ratio(vector<float> k_ratio);//�������ĸ�б������ȵ�����
	bool A_concentric(vector<Point2f>ccs, vector<float>radius);//A��ͬ��Բ����ɸѡ
	bool distance_compare(Point2f a,Point2f b,Point2f c,Point2f d);//�Ƚ������߶��Ƿ񳤶����
	float ratio_calculate(Point2f a, Point2f b);//����б��
	float distance_b(Point2f a, Point2f b);//������뺯��
	void change_corners(int a, int b, vector<Point2f>& corners);//����������Ԫ��
	void judging_condition(Mat src);//�����ж�������֤
	void filled_ratio();//������������4��б��
	void order_can();//����õ��˶����ݳ�order
	void roi_cut(Mat& src);//ROI����ü�
	void init_B();//B����ʼ��
	float distance_capture(Rect H_rect,Mat& src);
	void B_detection(Mat src);//B����⺯������
	void fill_extra(Mat src);//��B��roi����ȡW
	Point2f ann_b(Mat src);//B��svmʶ��W
	void B_svm_analyse(Mat srcImage);//B��ʶ��
	Point2f message_character;
	int compare = -1;

};

 
 
  
 


#endif // !FLY_H
