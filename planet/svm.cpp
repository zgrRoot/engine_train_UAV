//#include <opencv2\opencv.hpp>
//#include <opencv2\ml.hpp>
//#include <opencv2/cvconfig.h>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>    
//
//#include <io.h>
//#include <string>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//using namespace ml;
//
//
//#define CLASSSUM    4   // ͼƬ����26��
//#define IMAGE_ROWS  30   // ͳһͼƬ�߶�
//#define IMAGE_COLS  30   // ͳһͼƬ���
//#define IMAGESSUM   12   // ÿһ��ͼƬ����
//
//
//std::string dirNum[4] = { "A","B","C","H" };
//Mat trainingData = Mat::zeros(CLASSSUM*IMAGESSUM, IMAGE_ROWS*IMAGE_COLS, CV_32FC1);
//Mat labels = Mat::zeros(CLASSSUM*IMAGESSUM, 1, CV_32SC1);
//
// 
//
//int main()
//{
//
//	for (int i = 0; i < CLASSSUM; i++)
//	{
//		int k = 0;
//		std::string inPath = "D:\\data\\src\\" + dirNum[i] + "\\*.jpg";
//		intptr_t handle;
//		struct _finddata_t fileinfo;
//		handle = _findfirst(inPath.c_str(), &fileinfo);
//		if (handle == -1) return -1;
//
//		do {
//			std::string imgname = "D:/data/src/" + dirNum[i] + "/" + fileinfo.name;
//			cout << imgname << endl;
//			Mat srcImage = imread(imgname, 0);
//			if (srcImage.empty()) {
//				std::cout << "Read image error:" << imgname << std::endl;
//				return -1;
//			}
//			srcImage.convertTo(srcImage, CV_32FC1);
//			resize(srcImage, srcImage, Size(IMAGE_ROWS, IMAGE_COLS), (0, 0), (0, 0), INTER_AREA);
//
//			srcImage = srcImage.reshape(1, 1);
//
//			trainingData.push_back(srcImage);
//
//			labels.at<int>((i*IMAGESSUM + k), 0) = i;
//
//			k++;
//		} while (!_findnext(handle, &fileinfo) && k < IMAGESSUM);
//
//		/*Mat labelsMat(CLASSSUM*IMAGESSUM, CLASSSUM, CV_32FC1, labels);*/
//		_findclose(handle);
//	}
//
//	trainingData = trainingData(Range(CLASSSUM*IMAGESSUM, CLASSSUM*IMAGESSUM * 2), Range::all());
//
//	// ѵ���������ݼ���Ӧ��ǩ
//	/*Mat trainingDataMat(CLASSSUM*IMAGESSUM, IMAGE_ROWS*IMAGE_COLS, CV_32FC1, trainingData);
//	Mat labelsMat(CLASSSUM*IMAGESSUM, CLASSSUM, CV_32FC1, labels);*/
//
//	// ��ʼѵ��
//	cout << trainingData.size() << endl;
//	cout << labels.size() << endl;
//	Ptr<SVM>model = SVM::create();
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
//	Ptr<TrainData> tData = TrainData::create(trainingData, ROW_SAMPLE, labels); // ROW_SAMPLE��ʾһ��һ��
//
//	SVM_params->train(tData); // ѵ��
//	SVM_params->save("src3.xml");
//
//	// ����ѵ�����
//	/*cout << "------------------test-------------------" << endl;
//	TestXml();
//	cout << "------------------end-------------------" << endl;
//	waitKey(0);
//	while (1);
//	return 0;*/
//}
//
//
