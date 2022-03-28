//#include <stdio.h>  
//#include <time.h>  
//#include <opencv2/opencv.hpp>  
//#include <opencv/cv.h>  
//#include <iostream> 
//#include <opencv2/core/core.hpp>  
//#include <opencv2/highgui/highgui.hpp>  
//#include <opencv2/ml/ml.hpp>  
//#include <io.h>
// 
//
//using namespace std;
//using namespace cv;
// 
//
//void getFiles(string path, vector<string>& files);
//void get_A(Mat& trainingImages, vector<int>& trainingLabels);
//void get_B(Mat& trainingImages, vector<int>& trainingLabels);
//void get_C(Mat& trainingImages, vector<int>& trainingLabels);
//void get_H(Mat& trainingImages, vector<int>& trainingLabels);
// 
//int main()
//{
//	获取训练数据
//	Mat classes;
//	Mat trainingData;	
//	Mat trainingImages;
// 
//	  
//	vector<int> trainingLabels;
//
//	get_A(trainingImages, trainingLabels);
//	get_B(trainingImages, trainingLabels);
//	get_C(trainingImages, trainingLabels);
//	get_H(trainingImages, trainingLabels);
//
//	Mat(trainingImages).copyTo(trainingData);
//	trainingData.convertTo(trainingData, CV_32FC1);
//	Mat(trainingLabels).copyTo(classes);
//	配置SVM训练器参数
//	CvSVMParams SVM_params;
//	SVM_params.svm_type = CvSVM::C_SVC;
//	SVM_params.kernel_type = CvSVM::LINEAR;
//	SVM_params.degree = 0;
//	SVM_params.gamma = 1;
//	SVM_params.coef0 = 0;
//	SVM_params.C = 1;
//	SVM_params.nu = 0;
//	SVM_params.p = 0;
//	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 0.01);
//	训练
//	CvSVM svm;
//	svm.train(trainingData, classes, Mat(), Mat(), SVM_params);
//	保存模型
//	svm.save("svm.xml");
//	cout << "训练好了！！！" << endl;
//	getchar();
//	return 0;
//}
//void getFiles(string path, vector<string>& files)
//{
//	long   hFile = 0;
//	struct _finddata_t fileinfo;
//	string p;
//	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
//	{
//		do
//		{
//			if ((fileinfo.attrib &  _A_SUBDIR))
//			{
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
//			}
//			else
//			{
//				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//			}
//		} while (_findnext(hFile, &fileinfo) == 0);
//
//		_findclose(hFile);
//	}
//}
//void get_A(Mat& trainingImages, vector<int>& trainingLabels)
//{
//	string filePath = "D:\\data\\train_image\\A";
//	vector<string> files;
//	getFiles(filePath, files);
//	int number = files.size();
//	for (int i = 0; i < number; i++)
//	{
//		Mat  SrcImage = imread(files[i].c_str());
//		SrcImage = SrcImage.reshape(1, 1);
//		trainingImages.push_back(SrcImage);
//		trainingLabels.push_back(1);
//	}
//}
//void get_B(Mat& trainingImages, vector<int>& trainingLabels)
//{
//	string filePath = "D:\\data\\test_image\\B";
//	vector<string> files;
//	getFiles(filePath, files);
//	int number = files.size();
//	for (int i = 0; i < number; i++)
//	{
//		Mat  SrcImage = imread(files[i].c_str());
//		SrcImage = SrcImage.reshape(1, 1);
//		trainingImages.push_back(SrcImage);
//		trainingLabels.push_back(0);
//	}
//}
// 
//
//void get_C(Mat& trainingImages, vector<int>& trainingLabels)
//{
//	string filePath = "D:\\data\\train_image\\C";
//	vector<string> files;
//	getFiles(filePath, files);
//	int number = files.size();
//	for (int i = 0; i < number; i++)
//	{
//		Mat  SrcImage = imread(files[i].c_str());
//		SrcImage = SrcImage.reshape(1, 1);
//		trainingImages.push_back(SrcImage);
//		trainingLabels.push_back(1);
//	}
//}
//
//
//void get_H(Mat& trainingImages, vector<int>& trainingLabels)
//{
//	string filePath = "D:\\data\\train_image\\H";
//	vector<string> files;
//	getFiles(filePath, files);
//	int number = files.size();
//	for (int i = 0; i < number; i++)
//	{
//		Mat  SrcImage = imread(files[i].c_str());
//		SrcImage = SrcImage.reshape(1, 1);
//		trainingImages.push_back(SrcImage);
//		trainingLabels .push_back(1);
//	}
//}