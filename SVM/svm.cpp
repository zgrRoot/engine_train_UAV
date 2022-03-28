// 
// 
//#include<highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//
//
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
//using namespace cv;
//using namespace ml;
//using namespace std;
//
//
//void get_A(Mat& data, vector<int>& trainingLabels);
// 
//void get_C(Mat& data, vector<int>& trainingLabels);
// 
//void getFiles(string path, vector<string>& files);
//
//int main()
//{
//	 
//	Mat Data;
//	vector<int> Label;
//	Mat trainData;
//	Mat trainLabel;
//	get_A(Data, Label);
//	get_C(Data, Label);
//	Data.copyTo(trainData);
//	trainData.convertTo(trainData, CV_32FC1);
//	Mat(Label).copyTo(trainLabel);
//	 
//	 
//	 
//	 
//	 //创建SVM模型
//	Ptr<SVM> SVM_params = SVM::create();
//	SVM_params->setType(SVM::C_SVC); // C_SVC用于分类，C_SVR用于回归
//	SVM_params->setKernel(SVM::LINEAR); // LINEAR线性核函数，SIGMOID为高斯函数
//
//	SVM_params->setDegree(0); // 核函数中的参数degree，针对多项式核函数
//	SVM_params->setGamma(1); // 核函数中的参数gamma，针对多项式/RBF/SIGMOID函数
//	SVM_params->setCoef0(0); // 和函数中的参数，针对多项式/SIGMOID函数
//	SVM_params->setC(1); // SVM最优化问题参数，设置C_SVC, EPS_SVR和NU_SVR的参数
//	SVM_params->setNu(0); // SVM最优化问题参数，设置NU_SVC，ONE_ClASS,NU_SVR的参数
//	SVM_params->setP(0); // SVM最优化问题参数，设置 EPS_SVR中损失函数P的值
//
//	SVM_params->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 1000, 0.01));
//
//	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, trainLabel); // ROW_SAMPLE表示一行一个
//
//	SVM_params->train(tData); // 训练
//	SVM_params->save("area_ABCH1_svm.xml");
//	cout << "训练成功！\n" << endl;
//
//	//Mat src = imread("C:\\Users\\Lenovo\\Pictures\\1.png", 0);
//	//resize(src, src, Size(28, 28));
//	//if (!src.data)
//	//	cout << "图像识别失败" << endl;
//	///*imshow("识别图片", src);
//	//waitKey(0);*/
//
//	//src = src.reshape(1, 1); // 输入图片序列化
//	//Mat input;
//	//input.push_back(src);
//	//input.convertTo(input, CV_32FC1);
//
//	//float res = SVM_params->predict(input);
//	//cout << "结果是：" << res << endl;
//
//	//system("pause");
//	getchar();
//	return 0;
//}
// 
//
//
//
//void getFiles(string path, vector<string>& files)
//{
//	intptr_t   hFile = 0;
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
// 
//	 
//	 
// 
//void get_A(Mat& data, vector<int>& trainingLabels)
//{
//	string filePath = "D:\\data\\1";
//	vector<string> files;
//	getFiles(filePath, files);
//	int number = files.size();
//	for (int i = 0; i < number; i++)
//	{
//		Mat  SrcImage = imread(files[i].c_str());
//		//resize(SrcImage, SrcImage, Size(100, 100));
//
//		SrcImage = SrcImage.reshape(1, 1);
//		data.push_back(SrcImage);
//		trainingLabels.push_back(1);
//	}
//}
// 
//
//
//
//
//
//void get_C(Mat& data, vector<int>& trainingLabels)
//{
//	string filePath = "D:\\data\\0";
//	vector<string> files;
//	getFiles(filePath, files);
//	int number = files.size();
//	for (int i = 0; i < number; i++)
//	{
//		Mat  SrcImage = imread(files[i].c_str());
//		//resize(SrcImage, SrcImage, Size(100, 100));
//		SrcImage = SrcImage.reshape(1, 1);
//		data.push_back(SrcImage);
//		trainingLabels.push_back(0);
//	}
//}
// 