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
//#define CLASSSUM    4   // 图片共有26类
//#define IMAGE_ROWS  30   // 统一图片高度
//#define IMAGE_COLS  30   // 统一图片宽度
//#define IMAGESSUM   12   // 每一类图片张数
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
//	// 训练样本数据及对应标签
//	/*Mat trainingDataMat(CLASSSUM*IMAGESSUM, IMAGE_ROWS*IMAGE_COLS, CV_32FC1, trainingData);
//	Mat labelsMat(CLASSSUM*IMAGESSUM, CLASSSUM, CV_32FC1, labels);*/
//
//	// 开始训练
//	cout << trainingData.size() << endl;
//	cout << labels.size() << endl;
//	Ptr<SVM>model = SVM::create();
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
//	Ptr<TrainData> tData = TrainData::create(trainingData, ROW_SAMPLE, labels); // ROW_SAMPLE表示一行一个
//
//	SVM_params->train(tData); // 训练
//	SVM_params->save("src3.xml");
//
//	// 测试训练结果
//	/*cout << "------------------test-------------------" << endl;
//	TestXml();
//	cout << "------------------end-------------------" << endl;
//	waitKey(0);
//	while (1);
//	return 0;*/
//}
//
//
