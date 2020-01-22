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

Mat GetMeanFace(Mat& total);
Mat GetCovariance(Mat& total, Mat& meanface);

Mat preprocess(string dir, vector<string> filenames)
{
	Mat img, tmp, dst;
	Mat total(IMG_SIZE * IMG_SIZE, filenames.size(), CV_8UC1, Scalar(255));
	for (int i = 0; i < filenames.size(); i++)
	{
		img = imread(dir + filenames[i]);
		Rect rect(65, 55, 135, 190);
		img = img(rect);
		cvtColor(img, img, COLOR_RGB2GRAY);
		equalizeHist(img, img);
		resize(img, img, Size(IMG_SIZE, IMG_SIZE));
		tmp = img.reshape(1, IMG_SIZE*IMG_SIZE);
		tmp.col(0).copyTo(total.col(i));
	}
	return total;
}
void train(Mat total, string dir, int numofEigenface, string model)
{
	Mat meanface = GetMeanFace(total);//meanface : IMG_SIZE^2 * 1
	cout << "calculating the Covariance..." << endl;
	Mat Covariance = GetCovariance(total, meanface);//Covariance : IMG_SIZE^2 * IMG_SIZE^2

	Mat meanfaceMatrix(IMG_SIZE * IMG_SIZE, total.cols, CV_8UC1, Scalar(255));
	for (int i = 0; i < total.cols; i++)
	{
		meanface.copyTo(meanfaceMatrix.col(i));
	}
	Mat meanfaceMatrix_32F;
	meanfaceMatrix.convertTo(meanfaceMatrix_32F, CV_32FC1);
	Mat engValues, engVectors;
	Mat At( numofEigenface, IMG_SIZE * IMG_SIZE, CV_32FC1);
	/*
	@param eigenvalues output vector of eigenvalues of the same type as src; the eigenvalues are stored
	in the descending order.
	@param eigenvectors output matrix of eigenvectors; it has the same size and type as src; the
	eigenvectors are stored as subsequent matrix rows, in the same order as the corresponding
	eigenvalues.
	*/
	cout << "calculating the engValues and engVectors..." << endl;
	eigen(Covariance, engValues, engVectors);
	FileStorage fs("..\\model\\" + model + to_string(IMG_SIZE) + ".xml", FileStorage::WRITE);
	cout << "get the transform matrix and the max 10 engfaces..." << endl;
	//cout << "engValues :" << engValues << endl;
	for (int i = 0; i < numofEigenface; i++)
	{
		if (i < 10) {
			Mat face = engVectors.row(i).clone();
			//cout << face << endl;
			Mat r;
			normalize(face, r, 255.0, 0.0, NORM_MINMAX);
			Mat r_8U;
			r.convertTo(r_8U, CV_8UC1);
			//cout << r << endl;
			imwrite("engface" + to_string(i) + ".jpg", r_8U.reshape(0, IMG_SIZE));
		}
		engVectors.row(i).copyTo(At.row(i));
	}
	fs << "meanface" << meanface;
	fs << "A" << At.t();
	cout << "transorm the images in dataset and save..." << endl;
	Mat total_32F;
	total.convertTo(total_32F, CV_32FC1);
	Mat data = At * (total_32F-meanfaceMatrix_32F);
	fs << "data" << data;
	fs.release();
	/**/
}

int main(int argc, char * argv[])
{
	int eng = atoi(argv[1]);
	string model = string(argv[2]);
	string dir = string(argv[3]);
	vector<string> filenames = getFiles(dir + '*');
	generatemysample();
	Mat total = preprocess(dir, filenames);
	train(total, dir, 100, model);
	cout << "Done." << endl;
	int stop;
	cin >> stop;
	//imshow("test",total);
	//waitKey();
}

Mat GetMeanFace(Mat& total)
{
	Mat res = Mat::zeros(IMG_SIZE*IMG_SIZE, 1, CV_8UC1);
	uchar* p = res.ptr<uchar>(0);
	for (int i = 0; i < total.rows; i++)
	{
		p[i] = mean(total.row(i))[0];
	}
	Mat test = res.reshape(0, IMG_SIZE);
	imwrite("meanface.jpg", test);
	//imshow("meanface", test);
	//waitKey();
	return res;
}

Mat GetCovariance(Mat& total, Mat& meanface)
{
	Mat res = Mat::zeros(IMG_SIZE*IMG_SIZE, IMG_SIZE*IMG_SIZE, CV_32FC1);
	for (int i = 0; i < total.cols; i++)
	{
		Mat tmp = total.col(i) - meanface;
		Mat tmp_32F;
		tmp.convertTo(tmp_32F, CV_32FC1);
		//mulTransposed(total.col(i), tmp, false, meanface);
		//cout << tmp.size() << endl;
		res = res + tmp_32F * tmp_32F.t();
	}
	res = res / total.cols;
	//res.convertTo(res, CV_8UC1, 1, 0);
	return res;
}
