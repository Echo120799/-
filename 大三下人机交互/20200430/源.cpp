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
	Mat img;
	img = imread("lena.jpg");
	if (!img.data)return -1;
	namedWindow("ԭʼͼ��", CV_WINDOW_AUTOSIZE);
	imshow("ԭʼͼ��", img);

	//------------------ԭͼԤ����-----------------------------------
	Mat GRAY, EdgeCanny, EdgeSobel;
	
	//you code here --------------------------------------------------------------1
	//��ͼ���ͨ���������жϣ����ͨ����Ϊ3����ͼ��ת��Ϊ�Ҷ�ͼ
	cvtColor(img, GRAY, CV_RGB2GRAY);


 //------------------Canny��Ե���---------------------------
 //you code here---------------------------------------------------------------2
	 //����Canny��Ե��⣨��ֵһΪ50����ֵ��Ϊ150��
	Canny(GRAY, EdgeCanny, 50, 150, 3, false);

	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	imshow("Canny", EdgeCanny);



	//------------------Sobel��Ե���----------------------------------
	Mat absEdgeSobel, thEdgeSobel;

	//you code here----------------------------------------------------------------3
	//����sobel��Ե��Ⲣ��ʾ������ٽ�����ֵ������
	Sobel(GRAY, absEdgeSobel, -1, 1, 1, 3,  1,  0,BORDER_DEFAULT);
	convertScaleAbs(absEdgeSobel, absEdgeSobel);
	threshold(absEdgeSobel, thEdgeSobel, 20, 255, 0);
	


	namedWindow("Sobel", CV_WINDOW_AUTOSIZE);
	imshow("Sobel", absEdgeSobel);

	namedWindow("SobelFinal", CV_WINDOW_AUTOSIZE);
	imshow("SobelFinal", thEdgeSobel);



	waitKey(0);
	//destroyAllWindows();
	return 0;
}
