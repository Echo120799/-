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
	//����һ��ͼ��
	Mat img, mask,imggray;
	//img = imread("hand.bmp"); 
    
	img = imread("����.jpg"); 
	cvtColor(img, imggray, CV_RGB2GRAY);
	
	if (!img.data)return -1;
	namedWindow("ԭʼͼ��", CV_WINDOW_AUTOSIZE);
	//imshow("ԭʼͼ��", img);
	
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
	imwrite("��.png", result);

	/*
	//ת��ΪYCrCb��ɫ�ռ䣬����ʾ  
	//1.you code here/////////////////////////////////////////////////
	int dstCn = 0;
	cvtColor(img, imgDst, CV_RGB2YCrCb, dstCn);
	imshow("YCrCb", imgDst);
	

	//����ͨ��ͼ�����Ϊ�����ͨ��ͼ��,���� planes 
	 //2.you code here/////////////////////////////////////////////////
	Mat planes[3];
	split(imgDst, planes);

	//���õ��������ʾ���Ԫ��  
	MatIterator_<uchar> it_Cb = planes[1].begin<uchar>(),
		it_Cb_end = planes[1].end<uchar>();
	MatIterator_<uchar> it_Cr = planes[2].begin<uchar>();
	MatIterator_<uchar> it_skin = mask.begin<uchar>();


	/*for (; it_Cb != it_Cb_end; ++it_Cr, ++it_Cb, ++it_skin)
	{
		//���ݷ�ɫ��ֵ���mask
		//�˵�Ƥ����ɫ��YCbCrɫ�ȿռ�ķֲ���Χ:100<=Cb<=127, 138<=Cr<=170  
		//3.you code here/////////////////////////////////////////////////


		if (*it_Cb >= 75 && *it_Cb <= 127 && *it_Cr >= 130 && *it_Cr <= 170)
			*it_skin = 255;
		else
			*it_skin = 0;
	}
	//��ģ���ԭͼ��ȡ������Ȥ���򣬲���ʾ��ȡ����ͼ��
	//4.you code here/////////////////////////////////////////////////
	Mat result;
	img.copyTo(result,mask);

	namedWindow("��ȡ���ֲ�ͼ��", CV_WINDOW_AUTOSIZE);
	imshow("��ȡ���ֲ�ͼ��", result);

	//��mask����
	//���ͺ͸�ʴ�����Ϳ�������������ѷ��Žӣ�����ʴ��������ϸ��͹�𣨡��ߵ㡱������ 
	//��ʾ�ô�����mask����ȡ����ͼ��	
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
	namedWindow("����", CV_WINDOW_AUTOSIZE);
	imshow("����", result1);
	//cvDestroyWindow("ԭʼͼ��");
	//cvDestroyWindow("�����ͼ��");
	//cvDestroyWindow("����ͼ��");*/

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

	namedWindow("��ȡ���ֲ�ͼ��", CV_WINDOW_AUTOSIZE);
	imshow("��ȡ���ֲ�ͼ��", result);

	//��mask����
	//���ͺ͸�ʴ�����Ϳ�������������ѷ��Žӣ�����ʴ��������ϸ��͹�𣨡��ߵ㡱������ 
	//��ʾ�ô�����mask����ȡ����ͼ��	
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
	namedWindow("����", CV_WINDOW_AUTOSIZE);
	imshow("����", result1);
	waitKey(0);
	return 0;
	*/
}
