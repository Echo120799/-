#include <iostream>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <algorithm>

using namespace cv;
using namespace std;
//void skinExtract(const Mat &src, Mat &mask);
//double m[1][2] = { 103.0056,140.1309 };
//double c[2][2] = { 0.071,-0.041,-0.041,0.047 };

int main()
{
	//读入一张图像
	Mat img, mask,imggray;
	//img = imread("hand.bmp"); 
    
	img = imread("轮廓.jpg"); 
	cvtColor(img, imggray, CV_RGB2GRAY);
	
	if (!img.data)return -1;
	namedWindow("原始图像", CV_WINDOW_AUTOSIZE);
	//imshow("原始图像", img);
	
	Mat imgDst = img.clone();
	mask.create(imgDst.rows, imgDst.cols, CV_8UC1);

	for (int i = 0; i < img.rows; i++)
	{

		for (int j = 0; j < img.cols; j++)
		{
			if(imggray.ptr<uchar>(i)[j]==255)
				mask.ptr<uchar>(i)[j] = 0;
			else mask.ptr<uchar>(i)[j] = 255;

		}
	}
	Mat result;
	img.copyTo(result, mask);
	imwrite("画.png", result);

	/*
	//转换为YCrCb颜色空间，并显示  
	//1.you code here/////////////////////////////////////////////////
	int dstCn = 0;
	cvtColor(img, imgDst, CV_RGB2YCrCb, dstCn);
	imshow("YCrCb", imgDst);
	

	//将多通道图像分离为多个单通道图像,存入 planes 
	 //2.you code here/////////////////////////////////////////////////
	Mat planes[3];
	split(imgDst, planes);

	//运用迭代器访问矩阵元素  
	MatIterator_<uchar> it_Cb = planes[1].begin<uchar>(),
		it_Cb_end = planes[1].end<uchar>();
	MatIterator_<uchar> it_Cr = planes[2].begin<uchar>();
	MatIterator_<uchar> it_skin = mask.begin<uchar>();


	/*for (; it_Cb != it_Cb_end; ++it_Cr, ++it_Cb, ++it_skin)
	{
		//根据肤色阈值获得mask
		//人的皮肤颜色在YCbCr色度空间的分布范围:100<=Cb<=127, 138<=Cr<=170  
		//3.you code here/////////////////////////////////////////////////


		if (*it_Cb >= 75 && *it_Cb <= 127 && *it_Cr >= 130 && *it_Cr <= 170)
			*it_skin = 255;
		else
			*it_skin = 0;
	}
	//用模板和原图提取出感兴趣区域，并显示提取出的图像
	//4.you code here/////////////////////////////////////////////////
	Mat result;
	img.copyTo(result,mask);

	namedWindow("提取出手部图像", CV_WINDOW_AUTOSIZE);
	imshow("提取出手部图像", result);

	//对mask后处理
	//膨胀和腐蚀，膨胀可以填补凹洞（将裂缝桥接），腐蚀可以消除细的凸起（“斑点”噪声） 
	//显示用处理后的mask，提取出的图像	
	//5.you code here/////////////////////////////////////////////////
	Mat mask1;
	Mat mask2;
	Mat mask3;
	Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(mask, mask1, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(mask1, mask2, Mat(5, 5, CV_8UC1),anchor,iterations,borderType, borderValue);
	
	medianBlur(mask2, mask3,3);

	namedWindow("mask", CV_WINDOW_AUTOSIZE);
	imshow("mask", mask3);

	Mat result1;
	img.copyTo(result1, mask3);
	namedWindow("后处理", CV_WINDOW_AUTOSIZE);
	imshow("后处理", result1);
	//cvDestroyWindow("原始图像");
	//cvDestroyWindow("处理后图像");
	//cvDestroyWindow("后处理图像");*/

	/*
	double p[230][308];
	for (int i=0;i<img.rows;i++)
	{

		for (int j = 0; j < img.cols; j++)
		{
			double a = planes[1].ptr<uchar>(i)[j] - 103.0056;
			double b = planes[2].ptr<uchar>(i)[j] - 140.1309;
		    p[i][j] = exp(-0.5*(a * (0.0071*a - 0.0041*b) + b * (-0.0041*a + 0.0047*b)));

		}	
	}
	double max = p[0][0];
	for (int i = 0; i < img.rows; i++)
	{

		for (int j = 0; j < img.cols; j++)
		{
			if (p[i][j] > max)
				max = p[i][j];
		}
	}
	cout << max;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			p[i][j] = p[i][j] / max;
		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if(p[i][j]>0.055)
				mask.ptr<uchar>(i)[j] = 255;
			else mask.ptr<uchar>(i)[j] = 0;
		}
	}

	Mat result;
	img.copyTo(result, mask);

	namedWindow("提取出手部图像", CV_WINDOW_AUTOSIZE);
	imshow("提取出手部图像", result);

	//对mask后处理
	//膨胀和腐蚀，膨胀可以填补凹洞（将裂缝桥接），腐蚀可以消除细的凸起（“斑点”噪声） 
	//显示用处理后的mask，提取出的图像	
	//5.you code here/////////////////////////////////////////////////
	Mat mask1;
	Mat mask2;
	Mat mask3;
	Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(mask, mask1, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(mask1, mask2, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);

	medianBlur(mask2, mask3, 3);

	namedWindow("mask", CV_WINDOW_AUTOSIZE);
	imshow("mask", mask3);

	Mat result1;
	img.copyTo(result1, mask3);
	namedWindow("后处理", CV_WINDOW_AUTOSIZE);
	imshow("后处理", result1);
	waitKey(0);
	return 0;
	*/
}
