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
	//you code here1-------------------------------------------------����ͼ��
	img=imread("lena.jpg");
	if (!img.data)	{		printf("NO IMAGE DATA!");		return -1;	}
	//��ͼ��ת��Ϊ�Ҷ�ͼ��
	Mat gray_image;
	cvtColor(img, gray_image, COLOR_BGR2GRAY);
	//you code here2-------------------------------------------------���Ҷ�ͼ�񱣴�Ϊ�ļ�
	imwrite("�Ҷ�ͼ.jpg", gray_image);

	namedWindow("Lena", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray", CV_WINDOW_AUTOSIZE);
	//you code here3-------------------------------------------------����Ӧ��ͼ�������ʾ
	imshow("Lena", img);	imshow("Gray", gray_image);
//�رմ���֮�����ʾʱ��
	waitKey(0);
	return 0;
}