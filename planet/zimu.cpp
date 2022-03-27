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
//float trainingData[CLASSSUM*IMAGESSUM][IMAGE_ROWS*IMAGE_COLS] = { { 0 } };  // 每一行一个训练图片
//float labels[CLASSSUM*IMAGESSUM][CLASSSUM] = { { 0 } };                     // 训练样本标签
//
//void TestXml()
//{
//	Ptr<ANN_MLP> model = StatModel::load<ANN_MLP>("English.xml");
//
//	for (int dnum = 0; dnum < CLASSSUM; dnum++)
//	{
//		std::string inPath = "D:\\data\\english\\" + dirNum[dnum] + "\\*.jpg";
//		intptr_t handle;
//		struct _finddata_t fileinfo;
//		handle = _findfirst(inPath.c_str(), &fileinfo);
//		if (handle == -1) return;
//		int num = 0;
//		int imgok = 0;
//
//		int imgnum = 0;
//		do {
//			std::string imgname = "D:/data/english/" + dirNum[dnum] + "/" + fileinfo.name;
//			//cout << imgname << endl;
//			Mat srcImage = imread(imgname, 0);
//			//imshow("srcImage", srcImage);
//			//waitKey(1);
//			if (!srcImage.empty())
//			{
//				//将测试图像转化为1*128的向量
//				resize(srcImage, srcImage, Size(IMAGE_ROWS, IMAGE_COLS), (0, 0), (0, 0), INTER_AREA);
//				threshold(srcImage, srcImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//				Mat_<float> testMat(1, IMAGE_ROWS*IMAGE_COLS);
//				for (int i = 0; i < IMAGE_ROWS*IMAGE_COLS; i++) {
//					if (i >= 30 * 30 || i < 0) { cout << "vetcor下标越界" << endl; break; }
//					testMat.at<float>(0, i) = (float)srcImage.at<uchar>(i / IMAGE_ROWS, i % IMAGE_COLS);
//				}
//
//				//使用训练好的MLP model预测测试图像
//				Mat dst;
//				model->predict(testMat, dst);
//				//std::cout << "testMat: \n" << testMat << "\n" << std::endl;
//				//std::cout << "dst: \n" << dst << "\n" << std::endl;
//				double maxVal = 0;
//				Point maxLoc;
//				minMaxLoc(dst, NULL, &maxVal, NULL, &maxLoc);
//				std::cout  << dirNum[dnum] << " " << num++ << " 测试结果：" << dirNum[maxLoc.x] << "置信度:" << maxVal * 100 << "%" << std::endl;
//				if (dirNum[dnum] == dirNum[maxLoc.x]) {
//					imgok++;
//				}
//				else
//				{
//					std::string errPath = ".\\Image\\Error\\" + dirNum[dnum] + "\\" + fileinfo.name + " " + dirNum[maxLoc.x] + ".jpg";
//					// cout << errPath << endl;
//					imwrite(errPath, srcImage);
//				}
//				imgnum++;
//			}
//		} while (!_findnext(handle, &fileinfo) && imgnum < IMAGESSUM);
//
//		std::cout << dirNum[dnum] << " " << imgok << endl;
//		_findclose(handle);
//	}
//}
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
//
//			resize(srcImage, srcImage, Size(IMAGE_ROWS, IMAGE_COLS), (0, 0), (0, 0), INTER_AREA);
//			threshold(srcImage, srcImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//
//			for (int j = 0; j < IMAGE_ROWS*IMAGE_COLS; j++) {
//				trainingData[i*IMAGESSUM + k][j] = (float)srcImage.data[j];
//			}
//
//			// 设置标签数据
//			for (int j = 0; j < CLASSSUM; j++)
//			{
//				if (j == i)
//					labels[i*IMAGESSUM + k][j] = 1;
//				else
//					labels[i*IMAGESSUM + k][j] = 0;
//			}
//			k++;
//		} while (!_findnext(handle, &fileinfo) && k < IMAGESSUM);
//
//		Mat labelsMat(CLASSSUM*IMAGESSUM, CLASSSUM, CV_32FC1, labels);
//		_findclose(handle);
//	}
//
//	// 训练样本数据及对应标签
//	Mat trainingDataMat(CLASSSUM*IMAGESSUM, IMAGE_ROWS*IMAGE_COLS, CV_32FC1, trainingData);
//	Mat labelsMat(CLASSSUM*IMAGESSUM, CLASSSUM, CV_32FC1, labels);
//
//	// 开始训练
//	cout << trainingDataMat.size() << endl;
//	cout << labelsMat.size() << endl;
//	Ptr<ANN_MLP>model = ANN_MLP::create();
//	Mat layerSizes = (Mat_<int>(1, 5) << IMAGE_ROWS * IMAGE_COLS, 128, 128, 128, CLASSSUM);
//	model->setLayerSizes(layerSizes);
//	model->setTrainMethod(ANN_MLP::BACKPROP, 0.001, 0.1);
//	model->setActivationFunction(ANN_MLP::SIGMOID_SYM, 1.0, 1.0);
//	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 10000, 0.0001));
//	Ptr<TrainData> trainData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
//	model->train(trainData);
//	model->save("src.xml"); //保存训练结果
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
