//#include <iostream>
//#include<opencv2/opencv.hpp>
//#include<opencv2/ml.hpp>
//
//using namespace cv;
//using namespace ml;
//
//void findSamplecontours(InputArray src, OutputArrayOfArrays contours);
//
////使用SVM进行胶囊分类
//int main()
//{
//	//样本总类别数
//	const int classSum = 2;
//	////每个样本选取的特征个数
//	//const int featureSum = 3;
//	////训练样本总数
//	//const int sampleSum = 57;
//	//每种类别对应的名称
//	const std::string labelName[2] = { "green_peru", "brown" };
//	//训练数据及标签
//	Mat trainDataMat /*= Mat::zeros(sampleSum, featureSum, CV_32FC1)*/;
//	Mat labelsMat /*= Mat::zeros(sampleSum, 1, CV_32SC1)*/;
//	int k = 0;
//	/*创建训练数据*/
//		for (int label = 0; label < classSum; label++)
//		{
//			//训练图像所在文件夹
//			std::string path = "D:\\data\\train_image\\C\\";
//			char temp[256];
//			sprintf_s(temp, "%d", label);
//			path = path + temp + ".png";
//			Mat src = imread(path);
//			if (src.empty())
//			{
//				std::cout << "can not load image. \n" << std::endl;
//				return -1;
//			}
//			//imshow("input", src);
//			//获取每个胶囊的轮廓
//			std::vector<std::vector<Point>>contours;
//			findSamplecontours(src, contours);
//			for (int i = 0; i < contours.size(); i++)
//			{
//				if (contourArea(contours[i]) > 50)
//				{
//					//建立掩模MASK
//					Mat mask = Mat::zeros(src.size(), src.type());
//					drawContours(mask, contours, i, Scalar(255, 255, 255), -1);
//					//获得MASK对应区域的图像
//					src.copyTo(mask, mask);
//					//求各个通道的均值
//					Scalar maskSum = sum(mask);
//					maskSum = maskSum / contourArea(contours[i]);
//					//取前三个通道即BGR通道的均值作为特征
//					for (int j = 0; j < featureSum; j++)
//					{
//						trainDataMat.at<float>(k, j) = maskSum[j];
//					}
//					labelsMat.at<int>(k, 0) = label;
//					k++;
//				}
//			}
//		}
//	std::cout << "trainDataMat: \n" << trainDataMat << "\n" << std::endl;
//	std::cout << "labelsMat: \n" << labelsMat << "\n" << std::endl;
//
//	/*使用SVM训练部分*/
//		Ptr<SVM> model = SVM::create();
//	model->setType(SVM::C_SVC);
//	model->setKernel(SVM::POLY);
//	model->setDegree(1.0);
//	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
//	model->train(trainDataMat, ROW_SAMPLE, labelsMat);
//
//	/*测试部分*/
//		Mat testImg = imread("E:/image/image/classification/capsule/pills_test.png");
//	if (testImg.empty())
//	{
//		std::cout << "can not load image. \n" << std::endl;
//		return -1;
//	}
//	std::vector<std::vector<Point>>testContours;
//	findSamplecontours(testImg, testContours);
//	//对测试图像中的样本进行逐个判断
//	for (int i = 0; i < testContours.size(); i++)
//	{
//		if (contourArea(testContours[i]) > 50)
//		{
//			Mat testDataMat = Mat::zeros(1, featureSum, CV_32FC1);
//			Mat testLabelsMat;
//			Mat testMask = Mat::zeros(testImg.size(), testImg.type());
//			drawContours(testMask, testContours, i, Scalar(255, 255, 255), -1);
//			testImg.copyTo(testMask, testMask);
//			//求各个通道的均值
//			Scalar testMaskSum = sum(testMask);
//			testMaskSum = testMaskSum / contourArea(testContours[i]);
//			//取前三个通道即BGR通道的均值作为特征
//			for (int j = 0; j < featureSum; j++)
//			{
//				testDataMat.at<float>(0, j) = testMaskSum[j];
//			}
//			//使用训练好的SVM模型进行预测
//			model->predict(testDataMat, testLabelsMat);
//			//预测结果
//			int testLabel = testLabelsMat.at<float>(0, 0);
//			std::cout << "testLabel：\n" << labelName[testLabel] << std::endl;
//			//在测试图像上绘制出预测结果
//			RotatedRect minRect = minAreaRect(testContours[i]);
//			//使用对应颜色的矩形框将样本框选中
//			rectangle(testImg, minRect.boundingRect(), testMaskSum, 2, 8);
//			putText(testImg, labelName[testLabel], Point(minRect.boundingRect().x, minRect.boundingRect().y), 1, 1.5, Scalar(0, 255, 0), 2);
//			imshow("test image", testImg);
//			waitKey(2000);
//		}
//	}
//
//	waitKey();
//	return 0;
//}
//
//void findSamplecontours(InputArray src, OutputArrayOfArrays contours)
//{
//	Mat dst, blueChannels, redChannels;
//	std::vector<Mat>channels;
//	//将原图像分成多个单通道图像
//	split(src, channels);
//	blueChannels = channels.at(0);
//	redChannels = channels.at(2);
//	//分别在R通道和B通道使用不同的阈值进行二值化
//	threshold(redChannels, redChannels, 60, 255, THRESH_BINARY_INV);
//	threshold(blueChannels, blueChannels, 100, 255, THRESH_BINARY_INV);
//	//合并两个二值化后的区域
//	add(blueChannels, redChannels, dst);
//	//对获得区域进行闭操作，去除中心的小孔
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
//	morphologyEx(dst, dst, CV_MOP_CLOSE, kernel);
//	//腐蚀操作，去除部分过渡边缘
//	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
//	erode(dst, dst, kernel2);
//	//imshow("00", dst);
//	//waitKey();
//	Canny(dst, dst, 20, 100, 3, false);
//	std::vector<Vec4i>hierarchy;
//	//获取轮廓
//	findContours(dst, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//}
// 