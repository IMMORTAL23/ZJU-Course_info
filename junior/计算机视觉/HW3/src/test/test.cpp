#include<iostream>
#include <stdio.h>
#include <io.h>
#include<direct.h>
#include<string>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "GenerateMySample.h"
#define IMG_SIZE 64
using namespace std;
using namespace cv;
Mat preprocess(string dir)
{
	Mat demo = imread("../dataset/coursedata/KA.FE3.47.tiff");
	Mat img, tmp, dst;
	Mat total(IMG_SIZE * IMG_SIZE, 1, CV_8UC1, Scalar(255));
	img = imread(dir );
	imshow("input", img);
	waitKey(10);
	Mat img_align = alignImages(img, demo, dir);
	Rect rect(45, 61, 175, 175);
	img = img_align(rect);
	cvtColor(img, img, COLOR_RGB2GRAY);
	equalizeHist(img, img);
	resize(img, img, Size(IMG_SIZE, IMG_SIZE));
	tmp = img.reshape(1, IMG_SIZE*IMG_SIZE);
	tmp.col(0).copyTo(total.col(0));
	return total;
}

int main(int argc, char * argv[])
{
	Mat img = preprocess(string(argv[1]));
	Mat img_32F;
	img.convertTo(img_32F, CV_32FC1);
	string model = string(argv[2]);
	Mat A, data,meanface;
	FileStorage fs(model, FileStorage::READ);
	cout << "Loading..." << endl;
	fs["A"] >> A;
	fs["data"] >> data;
	fs["meanface"] >> meanface;
	Mat meanface_32F;
	meanface.convertTo(meanface_32F, CV_32FC1);
	Mat input = A.t() * (img_32F-meanface_32F);
	double min = 999999999999;
	int index = 0;
	for (int i = 0; i < data.cols; i++)
	{
		double tmp = (input - data.col(i)).dot(input - data.col(i));
		if (tmp < min) {
			min = tmp;
			index = i;
		}
	}
	Mat addeng = img_32F + A * data.col(index);
	Mat addeng_8U;
	Mat engface_32F = A * data.col(index);
	normalize(engface_32F, engface_32F, 255.0, 0.0, NORM_MINMAX);
	Mat engface_8U;
	engface_32F.convertTo(engface_8U, CV_8UC1);
	//imshow("engface", engface_8U.reshape(0,IMG_SIZE));
	addeng.convertTo(addeng_8U, CV_8UC1);
	vector<string> filenames = getFiles("..\\dataset\\coursedata\\*");
	cout << "result:" << filenames[index] << endl;
	Mat res = imread("..\\dataset\\coursedata\\" + filenames[index]);
	imshow("after preprocess", img.reshape(0, IMG_SIZE));
	//imwrite("afterpreprocess.png", img.reshape(0, IMG_SIZE));
	Mat tmp = addeng_8U.reshape(0, IMG_SIZE);
	//resize(tmp, tmp, Size(256, 256));
	imshow("addengi", tmp);
	imwrite("addengiface.png", tmp);
	imshow("output", res);
	waitKey(0);
}