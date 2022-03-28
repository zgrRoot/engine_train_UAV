/*
#include<iostream>
#include<opencv2/ml/ml.hpp>
#include<highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;
using namespace ml;

int main() {
	Mat img = imread("digits.png", 0);
	imshow("数据", img);
	int boot = 20;
	int m = img.rows / boot;
	int n = img.cols / boot;
	Mat data, labels;

	for (int i = 0; i < n; i++) {
		int colNum = i * boot;
		for (int j = 0; j < m; j++) {
			int rowNum = j * boot;
			Mat tmp;
			img(Range(rowNum, rowNum + boot), Range(colNum, colNum + boot)).copyTo(tmp);
			data.push_back(tmp.reshape(1, 1));
			labels.push_back((int)j / 5);

		}
	}
	data.convertTo(data, CV_32F);
	int sampleNum = data.rows;
	int trainNum = 3000;
	Mat trainData, trainLabel;
	trainData = data(Range(0, trainNum), Range::all());
	trainLabel = labels(Range(0, trainNum), Range::all());
	 //KNN
	int k =5;
	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, trainLabel);
	Ptr<KNearest>model = KNearest::create();
	model->setDefaultK(k);//k 最近项
	model->setIsClassifier(true);//true 分类 false 回归
	model->train(tData);

	double train_hr = 0, test_hr = 0;
	Mat reponse;
	for (int i = 0; i < sampleNum; i++) {
		Mat sample = data.row(i);
		float r = model->predict(sample);
		r = abs(r - labels.at<int>(i));
		if (r <= FLT_EPSILON)
			r = 1.f;
		else
			r = 0.f;
		if (i < trainNum)
			train_hr = train_hr + r;
		else
			test_hr = test_hr + r;
	}
	cout << test_hr << " " << test_hr << endl;
	cout << ":Knn模型在训练集上的准确率" << train_hr / trainNum * 100 <<
		"%,在测试集上的准确率为" << test_hr / (data.rows - trainNum)*100 << " " << endl;
	
	
	
	
	waitKey(0);
	return 0;

	
}*/