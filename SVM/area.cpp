//#include <iostream>
//#include<opencv2/opencv.hpp>
//#include<opencv2/ml.hpp>
//
//using namespace cv;
//using namespace ml;
//
//void findSamplecontours(InputArray src, OutputArrayOfArrays contours);
//
////ʹ��SVM���н��ҷ���
//int main()
//{
//	//�����������
//	const int classSum = 2;
//	////ÿ������ѡȡ����������
//	//const int featureSum = 3;
//	////ѵ����������
//	//const int sampleSum = 57;
//	//ÿ������Ӧ������
//	const std::string labelName[2] = { "green_peru", "brown" };
//	//ѵ�����ݼ���ǩ
//	Mat trainDataMat /*= Mat::zeros(sampleSum, featureSum, CV_32FC1)*/;
//	Mat labelsMat /*= Mat::zeros(sampleSum, 1, CV_32SC1)*/;
//	int k = 0;
//	/*����ѵ������*/
//		for (int label = 0; label < classSum; label++)
//		{
//			//ѵ��ͼ�������ļ���
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
//			//��ȡÿ�����ҵ�����
//			std::vector<std::vector<Point>>contours;
//			findSamplecontours(src, contours);
//			for (int i = 0; i < contours.size(); i++)
//			{
//				if (contourArea(contours[i]) > 50)
//				{
//					//������ģMASK
//					Mat mask = Mat::zeros(src.size(), src.type());
//					drawContours(mask, contours, i, Scalar(255, 255, 255), -1);
//					//���MASK��Ӧ�����ͼ��
//					src.copyTo(mask, mask);
//					//�����ͨ���ľ�ֵ
//					Scalar maskSum = sum(mask);
//					maskSum = maskSum / contourArea(contours[i]);
//					//ȡǰ����ͨ����BGRͨ���ľ�ֵ��Ϊ����
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
//	/*ʹ��SVMѵ������*/
//		Ptr<SVM> model = SVM::create();
//	model->setType(SVM::C_SVC);
//	model->setKernel(SVM::POLY);
//	model->setDegree(1.0);
//	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
//	model->train(trainDataMat, ROW_SAMPLE, labelsMat);
//
//	/*���Բ���*/
//		Mat testImg = imread("E:/image/image/classification/capsule/pills_test.png");
//	if (testImg.empty())
//	{
//		std::cout << "can not load image. \n" << std::endl;
//		return -1;
//	}
//	std::vector<std::vector<Point>>testContours;
//	findSamplecontours(testImg, testContours);
//	//�Բ���ͼ���е�������������ж�
//	for (int i = 0; i < testContours.size(); i++)
//	{
//		if (contourArea(testContours[i]) > 50)
//		{
//			Mat testDataMat = Mat::zeros(1, featureSum, CV_32FC1);
//			Mat testLabelsMat;
//			Mat testMask = Mat::zeros(testImg.size(), testImg.type());
//			drawContours(testMask, testContours, i, Scalar(255, 255, 255), -1);
//			testImg.copyTo(testMask, testMask);
//			//�����ͨ���ľ�ֵ
//			Scalar testMaskSum = sum(testMask);
//			testMaskSum = testMaskSum / contourArea(testContours[i]);
//			//ȡǰ����ͨ����BGRͨ���ľ�ֵ��Ϊ����
//			for (int j = 0; j < featureSum; j++)
//			{
//				testDataMat.at<float>(0, j) = testMaskSum[j];
//			}
//			//ʹ��ѵ���õ�SVMģ�ͽ���Ԥ��
//			model->predict(testDataMat, testLabelsMat);
//			//Ԥ����
//			int testLabel = testLabelsMat.at<float>(0, 0);
//			std::cout << "testLabel��\n" << labelName[testLabel] << std::endl;
//			//�ڲ���ͼ���ϻ��Ƴ�Ԥ����
//			RotatedRect minRect = minAreaRect(testContours[i]);
//			//ʹ�ö�Ӧ��ɫ�ľ��ο�������ѡ��
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
//	//��ԭͼ��ֳɶ����ͨ��ͼ��
//	split(src, channels);
//	blueChannels = channels.at(0);
//	redChannels = channels.at(2);
//	//�ֱ���Rͨ����Bͨ��ʹ�ò�ͬ����ֵ���ж�ֵ��
//	threshold(redChannels, redChannels, 60, 255, THRESH_BINARY_INV);
//	threshold(blueChannels, blueChannels, 100, 255, THRESH_BINARY_INV);
//	//�ϲ�������ֵ���������
//	add(blueChannels, redChannels, dst);
//	//�Ի��������бղ�����ȥ�����ĵ�С��
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
//	morphologyEx(dst, dst, CV_MOP_CLOSE, kernel);
//	//��ʴ������ȥ�����ֹ��ɱ�Ե
//	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
//	erode(dst, dst, kernel2);
//	//imshow("00", dst);
//	//waitKey();
//	Canny(dst, dst, 20, 100, 3, false);
//	std::vector<Vec4i>hierarchy;
//	//��ȡ����
//	findContours(dst, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//}
// 