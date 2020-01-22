#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
/**
* @function: 获取cate_dir目录下的所有文件名
* @param: cate_dir - string类型
* @result：vector<string>类型
*/
vector<string> getFiles(string cate_dir);
/**
* @function: 获取src人脸眼睛的坐标
* @param: src - 人脸图片     eyes[2] - 输出的坐标位置
*/
void DetectEye(Mat src, Point(&eyes)[2]);
/**
* @function: 根据眼睛坐标对图像进行仿射变换使他和模板对齐
* @param: src - 待对齐人脸图片 dst - 模板图像
*/
Mat alignImages(Mat& src, Mat& dst);
void generatemysample();