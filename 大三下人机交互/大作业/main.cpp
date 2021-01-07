#include <iostream>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <algorithm>

using namespace cv;
using namespace std;

Mat nail_bianyuan(Mat image_roi, Mat img);
Mat thresh_callback(int, void*, Mat dst, int thresh, Mat drawing);


int main()
{
	//读入一张图像
	Mat img, mask;
	img = imread("hand.jpg");
	if (!img.data)
		return -1;
	namedWindow("原始图像", CV_WINDOW_AUTOSIZE);
	imshow("原始图像", img);

	Mat imgDst = img.clone();
	mask.create(imgDst.rows, imgDst.cols, CV_8UC1);


	//转换为YCrCb颜色空间，并显示  
	int dstCn = 0;
	cvtColor(img, imgDst, CV_RGB2YCrCb, dstCn);
	//imshow("YCrCb", imgDst);


	//将多通道图像分离为多个单通道图像,存入 planes 
	Mat planes[3];
	split(imgDst, planes);

	//运用迭代器访问矩阵元素  
	MatIterator_<uchar> it_Cb = planes[1].begin<uchar>(),
		it_Cb_end = planes[1].end<uchar>();
	MatIterator_<uchar> it_Cr = planes[2].begin<uchar>();
	MatIterator_<uchar> it_skin = mask.begin<uchar>();

	for (; it_Cb != it_Cb_end; ++it_Cr, ++it_Cb, ++it_skin)
	{
		//根据肤色阈值获得mask
		if (*it_Cb >= 110 && *it_Cb <= 130 && *it_Cr >= 140 && *it_Cr <= 175)
			*it_skin = 255;
		else
			*it_skin = 0;
	}

	//用模板和原图提取出感兴趣区域，并显示提取出的图像
	Mat result;
	img.copyTo(result, mask);
	//namedWindow("提取出手部图像", CV_WINDOW_AUTOSIZE);
	//imshow("提取出手部图像", result);

	//对mask后处理
	//膨胀和腐蚀，膨胀可以填补凹洞（将裂缝桥接），腐蚀可以消除细的凸起（“斑点”噪声） 
	Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(mask, mask, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(mask, mask, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);

	//中值滤波
	medianBlur(mask, mask, 3);

	//namedWindow("mask", CV_WINDOW_AUTOSIZE);
	//imshow("mask", mask);

	img.copyTo(result, mask);
	namedWindow("后处理", CV_WINDOW_AUTOSIZE);
	imshow("后处理", result);

	//画出手外部轮廓
	vector<vector<Point> > contours;
	findContours(mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point());
	int index;
	double area, maxArea(0);
	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(Mat(contours[i]));
		if (area > maxArea)
		{
			maxArea = area;
			index = i;
		}
	}
	Mat contoursImage(mask.rows, mask.cols, CV_8U, Scalar(0));
	drawContours(contoursImage, contours, index, Scalar(255), 1);
	namedWindow("轮廓", CV_WINDOW_AUTOSIZE);
	imshow("轮廓", contoursImage);

	//计算图像重心
	Moments moment = moments(mask, true);
	Point center(moment.m10 / moment.m00, moment.m01 / moment.m00);
	//circle(mask, center, 8, Scalar(0, 0, 255), CV_FILLED);
	//imshow("重心", mask);

	// 寻找指尖（遍历轮廓所有点，比较到手心（重心）的距离）
	vector<Point> couPoint = contours[index];
	vector<Point> fingerTips;//指尖坐标
	Point tmp;
	int max(0), count(0), notice(0);
	for (int i = 0; i < couPoint.size(); i++)
	{
		tmp = couPoint[i];
		int dist = (tmp.x - center.x) * (tmp.x - center.x) + (tmp.y - center.y) * (tmp.y - center.y);
		if (dist > max)
		{
			max = dist;
			notice = i;
		}

		// 计算最大值保持的点数，如果大于200,那么就认为这个是指尖
		if (dist != max)
		{
			count++;
			if (count > 200)
			{
				count = 0;
				max = 0;
				bool flag = false;
				// 低于手心的点不算
				if (center.y < couPoint[notice].y)
					continue;
				if (flag)
					continue;
				fingerTips.push_back(couPoint[notice]);
				//circle(result, couPoint[notice], 6, Scalar(0, 255, 0), CV_FILLED);
				//line(result, center, couPoint[notice], Scalar(255, 0, 0), 2);

			}
		}

	}
	//imshow("五个指尖", result);//标出五个指尖

	//选择一个指尖（目前是中指）
	int a = fingerTips[0].x;
	int b = fingerTips[0].y;
	Rect rect(a - 20, b - 10, 60, 60);
	Mat roi = result(rect);//此处roi是引用的result，对image_roi进行改动，result也会随之变化
	imshow("指尖", roi);

	
	//提取指甲边缘
	Mat dst=nail_bianyuan(roi, img);
	
	//填充指甲轮廓
	int thresh = 100;
	int max_thresh = 255;
	Mat drawing;
	blur(dst, dst, Size(3, 3));
	const char* source_window = "Source";
	//namedWindow(source_window, WINDOW_AUTOSIZE);
	//imshow(source_window, dst);
	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh);
	drawing=thresh_callback(0, 0,dst,thresh,drawing);
	
	//指甲贴图
	Mat pic = imread("指甲.png");//贴图png
	for (int i = 0; i < drawing.rows; i++)
	{
		for (int j = 0; j < drawing.cols; j++)
		{
			if (drawing.ptr<uchar>(i)[j] == 255)
				for (int c = 0; c < 3; c++)
				{
					roi.data[i*roi.step + roi.channels()*j + c]
						= roi.data[i*roi.step + roi.channels()*j + c] * (1 - 0.4) + pic.data[i*pic.step + pic.channels()*j + c] * 0.4;
				}
		}
	}
	imshow("all", result);
	
	waitKey(0);
}
Mat nail_bianyuan(Mat image_roi,Mat img)
{
	Mat DstPic, grayImage, edge;

	//创建与src同类型和同大小的矩阵
	DstPic.create(image_roi.size(), img.type());

	//将原始图转化为灰度图
	cvtColor(image_roi, grayImage, COLOR_BGR2GRAY);

	//先使用3*3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	//运行canny算子
	Canny(edge, edge, 100, 10, 3);

	namedWindow("边缘提取效果");
	namedWindow("处理后的边缘提取效果");

	//形态学滤波：闭操作
	Mat kernel, dst;
	kernel = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
	morphologyEx(edge, dst, MORPH_CLOSE, kernel);
	//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	//erode(dst, dst, element);
	//dilate(dst, dst, element);

	imshow("边缘提取效果", edge);
	imshow("处理后的边缘提取效果", dst);

	//dst.convertTo(dst, CV_32F);
	//imwrite("by.jpg", dst);

	return dst;

	
	
}
Mat thresh_callback(int, void*,Mat dst ,int thresh,Mat drawing)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny(dst, canny_output, thresh, thresh * 2, 3);
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	drawing = Mat::zeros(canny_output.size(), CV_8UC1);
	//for (size_t i = 0; i< contours.size(); i++)
	//{
	//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	drawContours(drawing, contours, 1, Scalar(255, 255, 255), CV_FILLED);
	//}
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
	return drawing;
	//drawing.convertTo(drawing, CV_32F);
	//imwrite("lk", drawing);

}