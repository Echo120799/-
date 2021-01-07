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
	Mat img, mask1;
	img = imread("test.jpg");
	if (!img.data)return -1;
	namedWindow("原始图像", CV_WINDOW_AUTOSIZE);
	imshow("原始图像", img);
	Mat imgDst = img.clone();

	//you code here 1--------------------------------------------------------转换为HSV颜色空间  
	int dstCn = 0;
	cvtColor(img, imgDst, CV_BGR2HSV,dstCn);

	//you code here 2----------------------------------------将多通道图像分离为多个单通道图像并显示H通道
	vector<Mat> planes;
	split(imgDst, planes);
	Mat Himg = planes.at(0);

	namedWindow("H通道", CV_WINDOW_AUTOSIZE);
	imshow("H通道", Himg);

	//you code here 3-------------------------------------------对H通道进行阈值化并显示阈值化之后的H通道
	Mat Hue;
	threshold(Himg, Hue, 100, 255, 0);
	namedWindow("阈值化之后H通道", CV_WINDOW_AUTOSIZE);
	imshow("阈值化之后H通道", Hue);

	//you code here 4------------------------------------------进行膨胀腐蚀
	//膨胀和腐蚀，膨胀可以填补凹洞（将裂缝桥接），腐蚀可以消除细的凸起（“斑点”噪声）  
	/*Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(Hue, Hue, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(Hue, Hue, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);


	medianBlur(Hue, Hue, 5);
	namedWindow("形态学处理之后H通道", CV_WINDOW_AUTOSIZE);
	imshow("形态学处理之后H通道", Hue);*/

	//寻找连通区域
	vector<vector<Point> > contours;
	//you code here 4--------------------------------------------找出所有外轮廓
	findContours(Hue, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	

    //去除小面积区域
	Mat contoursImage(Hue.rows,Hue.cols,CV_8U, Scalar(0));
	for (int i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) > 2000)
		{
			drawContours(contoursImage, contours, i, Scalar(255), CV_FILLED);
		}
			
	}

	namedWindow("轮廓", CV_WINDOW_AUTOSIZE);
	imshow("轮廓", contoursImage);

	waitKey(0);
	return 0;
}