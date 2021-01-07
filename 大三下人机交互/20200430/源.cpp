#include <iostream>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

int main()
{
	//读入一张图像
	Mat img;
	img = imread("lena.jpg");
	if (!img.data)return -1;
	namedWindow("原始图像", CV_WINDOW_AUTOSIZE);
	imshow("原始图像", img);

	//------------------原图预处理-----------------------------------
	Mat GRAY, EdgeCanny, EdgeSobel;
	
	//you code here --------------------------------------------------------------1
	//对图像的通道数进行判断，如果通道数为3，则将图像转换为灰度图
	cvtColor(img, GRAY, CV_RGB2GRAY);


 //------------------Canny边缘检测---------------------------
 //you code here---------------------------------------------------------------2
	 //进行Canny边缘检测（阈值一为50，阈值二为150）
	Canny(GRAY, EdgeCanny, 50, 150, 3, false);

	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	imshow("Canny", EdgeCanny);



	//------------------Sobel边缘检测----------------------------------
	Mat absEdgeSobel, thEdgeSobel;

	//you code here----------------------------------------------------------------3
	//进行sobel边缘检测并显示结果，再进行阈值化处理
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
