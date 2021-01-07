#include <iostream>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat img;
	//you code here1-------------------------------------------------读入图像
	img=imread("lena.jpg");
	if (!img.data)	{		printf("NO IMAGE DATA!");		return -1;	}
	//将图像转化为灰度图像
	Mat gray_image;
	cvtColor(img, gray_image, COLOR_BGR2GRAY);
	//you code here2-------------------------------------------------将灰度图像保存为文件
	imwrite("灰度图.jpg", gray_image);

	namedWindow("Lena", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray", CV_WINDOW_AUTOSIZE);
	//you code here3-------------------------------------------------对相应的图像进行显示
	imshow("Lena", img);	imshow("Gray", gray_image);
//关闭窗口之间的显示时间
	waitKey(0);
	return 0;
}