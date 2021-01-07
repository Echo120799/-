#include <iostream>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;



int main()
{
	//����һ��ͼ��
	Mat img, mask1;
	img = imread("test.jpg");
	if (!img.data)return -1;
	namedWindow("ԭʼͼ��", CV_WINDOW_AUTOSIZE);
	imshow("ԭʼͼ��", img);
	Mat imgDst = img.clone();

	//you code here 1--------------------------------------------------------ת��ΪHSV��ɫ�ռ�  
	int dstCn = 0;
	cvtColor(img, imgDst, CV_BGR2HSV,dstCn);

	//you code here 2----------------------------------------����ͨ��ͼ�����Ϊ�����ͨ��ͼ����ʾHͨ��
	vector<Mat> planes;
	split(imgDst, planes);
	Mat Himg = planes.at(0);

	namedWindow("Hͨ��", CV_WINDOW_AUTOSIZE);
	imshow("Hͨ��", Himg);

	//you code here 3-------------------------------------------��Hͨ��������ֵ������ʾ��ֵ��֮���Hͨ��
	Mat Hue;
	threshold(Himg, Hue, 100, 255, 0);
	namedWindow("��ֵ��֮��Hͨ��", CV_WINDOW_AUTOSIZE);
	imshow("��ֵ��֮��Hͨ��", Hue);

	//you code here 4------------------------------------------�������͸�ʴ
	//���ͺ͸�ʴ�����Ϳ�������������ѷ��Žӣ�����ʴ��������ϸ��͹�𣨡��ߵ㡱������  
	/*Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(Hue, Hue, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(Hue, Hue, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);


	medianBlur(Hue, Hue, 5);
	namedWindow("��̬ѧ����֮��Hͨ��", CV_WINDOW_AUTOSIZE);
	imshow("��̬ѧ����֮��Hͨ��", Hue);*/

	//Ѱ����ͨ����
	vector<vector<Point> > contours;
	//you code here 4--------------------------------------------�ҳ�����������
	findContours(Hue, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	

    //ȥ��С�������
	Mat contoursImage(Hue.rows,Hue.cols,CV_8U, Scalar(0));
	for (int i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) > 2000)
		{
			drawContours(contoursImage, contours, i, Scalar(255), CV_FILLED);
		}
			
	}

	namedWindow("����", CV_WINDOW_AUTOSIZE);
	imshow("����", contoursImage);

	waitKey(0);
	return 0;
}