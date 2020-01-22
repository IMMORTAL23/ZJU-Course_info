#include<iostream>
#include<opencv2/opencv.hpp>
#include<direct.h>
#include<string>
#include<opencv2/core/core.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("rice.png"); 
	//Mat src = imread("coins.jpg");
	if (src.empty())
	{
		cout << "路径错误" << endl;
		system("pause");
		return 0;
	}
	Scalar fitEllipseColor = Scalar(0, 0, 255);
	RotatedRect box;
	int sliderPos = 110;// 灰度图 -> 二值图的阈值（经验值）
	Mat greysrc;
	cvtColor(src, greysrc, CV_RGB2GRAY); // 彩色 -> 灰度图
	Mat binsrc = greysrc >= sliderPos;   // 灰度图 -> 二值图
	//bitwise_not(binsrc, binsrc); // 黑白反转
								 //轮廓
	vector<vector<Point>> contours;

	//使用canny检测出边缘
	Mat edge_image;
	Canny(binsrc, edge_image, 30, 70);
	imshow("canny边缘", edge_image);

	//边缘追踪，没有存储边缘的组织结构
	findContours(edge_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t count = contours[i].size();
		if (count < 6)  //拟合的点至少为6
			continue;
		RotatedRect box = fitEllipse(contours[i]);
		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)  //如果长宽比大于30，则排除，不做拟合
			continue;
		//drawContours(src, contours, (int)i, Scalar::all(255), 1, 8);//画出追踪出的轮廓
		ellipse(src, box, Scalar(0, 0, 255), 1, LINE_AA);   //画出拟合的椭圆
	}
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}