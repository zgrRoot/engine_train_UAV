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
//	 //����SVMģ��
//	Ptr<SVM> SVM_params = SVM::create();
//	SVM_params->setType(SVM::C_SVC); // C_SVC���ڷ��࣬C_SVR���ڻع�
//	SVM_params->setKernel(SVM::LINEAR); // LINEAR���Ժ˺�����SIGMOIDΪ��˹����
//
//	SVM_params->setDegree(0); // �˺����еĲ���degree����Զ���ʽ�˺���
//	SVM_params->setGamma(1); // �˺����еĲ���gamma����Զ���ʽ/RBF/SIGMOID����
//	SVM_params->setCoef0(0); // �ͺ����еĲ�������Զ���ʽ/SIGMOID����
//	SVM_params->setC(1); // SVM���Ż��������������C_SVC, EPS_SVR��NU_SVR�Ĳ���
//	SVM_params->setNu(0); // SVM���Ż��������������NU_SVC��ONE_ClASS,NU_SVR�Ĳ���
//	SVM_params->setP(0); // SVM���Ż�������������� EPS_SVR����ʧ����P��ֵ
//
//	SVM_params->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 1000, 0.01));
//
//	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, trainLabel); // ROW_SAMPLE��ʾһ��һ��
//
//	SVM_params->train(tData); // ѵ��
//	SVM_params->save("area_ABCH1_svm.xml");
//	cout << "ѵ���ɹ���\n" << endl;
//
//	//Mat src = imread("C:\\Users\\Lenovo\\Pictures\\1.png", 0);
//	//resize(src, src, Size(28, 28));
//	//if (!src.data)
//	//	cout << "ͼ��ʶ��ʧ��" << endl;
//	///*imshow("ʶ��ͼƬ", src);
//	//waitKey(0);*/
//
//	//src = src.reshape(1, 1); // ����ͼƬ���л�
//	//Mat input;
//	//input.push_back(src);
//	//input.convertTo(input, CV_32FC1);
//
//	//float res = SVM_params->predict(input);
//	//cout << "����ǣ�" << res << endl;
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