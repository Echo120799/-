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
	//����һ��ͼ��
	Mat img, mask;
	img = imread("hand.jpg");
	if (!img.data)
		return -1;
	namedWindow("ԭʼͼ��", CV_WINDOW_AUTOSIZE);
	imshow("ԭʼͼ��", img);

	Mat imgDst = img.clone();
	mask.create(imgDst.rows, imgDst.cols, CV_8UC1);


	//ת��ΪYCrCb��ɫ�ռ䣬����ʾ  
	int dstCn = 0;
	cvtColor(img, imgDst, CV_RGB2YCrCb, dstCn);
	//imshow("YCrCb", imgDst);


	//����ͨ��ͼ�����Ϊ�����ͨ��ͼ��,���� planes 
	Mat planes[3];
	split(imgDst, planes);

	//���õ��������ʾ���Ԫ��  
	MatIterator_<uchar> it_Cb = planes[1].begin<uchar>(),
		it_Cb_end = planes[1].end<uchar>();
	MatIterator_<uchar> it_Cr = planes[2].begin<uchar>();
	MatIterator_<uchar> it_skin = mask.begin<uchar>();

	for (; it_Cb != it_Cb_end; ++it_Cr, ++it_Cb, ++it_skin)
	{
		//���ݷ�ɫ��ֵ���mask
		if (*it_Cb >= 110 && *it_Cb <= 130 && *it_Cr >= 140 && *it_Cr <= 175)
			*it_skin = 255;
		else
			*it_skin = 0;
	}

	//��ģ���ԭͼ��ȡ������Ȥ���򣬲���ʾ��ȡ����ͼ��
	Mat result;
	img.copyTo(result, mask);
	//namedWindow("��ȡ���ֲ�ͼ��", CV_WINDOW_AUTOSIZE);
	//imshow("��ȡ���ֲ�ͼ��", result);

	//��mask����
	//���ͺ͸�ʴ�����Ϳ�������������ѷ��Žӣ�����ʴ��������ϸ��͹�𣨡��ߵ㡱������ 
	Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(mask, mask, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(mask, mask, Mat(5, 5, CV_8UC1), anchor, iterations, borderType, borderValue);

	//��ֵ�˲�
	medianBlur(mask, mask, 3);

	//namedWindow("mask", CV_WINDOW_AUTOSIZE);
	//imshow("mask", mask);

	img.copyTo(result, mask);
	namedWindow("����", CV_WINDOW_AUTOSIZE);
	imshow("����", result);

	//�������ⲿ����
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
	namedWindow("����", CV_WINDOW_AUTOSIZE);
	imshow("����", contoursImage);

	//����ͼ������
	Moments moment = moments(mask, true);
	Point center(moment.m10 / moment.m00, moment.m01 / moment.m00);
	//circle(mask, center, 8, Scalar(0, 0, 255), CV_FILLED);
	//imshow("����", mask);

	// Ѱ��ָ�⣨�����������е㣬�Ƚϵ����ģ����ģ��ľ��룩
	vector<Point> couPoint = contours[index];
	vector<Point> fingerTips;//ָ������
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

		// �������ֵ���ֵĵ������������200,��ô����Ϊ�����ָ��
		if (dist != max)
		{
			count++;
			if (count > 200)
			{
				count = 0;
				max = 0;
				bool flag = false;
				// �������ĵĵ㲻��
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
	//imshow("���ָ��", result);//������ָ��

	//ѡ��һ��ָ�⣨Ŀǰ����ָ��
	int a = fingerTips[0].x;
	int b = fingerTips[0].y;
	Rect rect(a - 20, b - 10, 60, 60);
	Mat roi = result(rect);//�˴�roi�����õ�result����image_roi���иĶ���resultҲ����֮�仯
	imshow("ָ��", roi);

	
	//��ȡָ�ױ�Ե
	Mat dst=nail_bianyuan(roi, img);
	
	//���ָ������
	int thresh = 100;
	int max_thresh = 255;
	Mat drawing;
	blur(dst, dst, Size(3, 3));
	const char* source_window = "Source";
	//namedWindow(source_window, WINDOW_AUTOSIZE);
	//imshow(source_window, dst);
	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh);
	drawing=thresh_callback(0, 0,dst,thresh,drawing);
	
	//ָ����ͼ
	Mat pic = imread("ָ��.png");//��ͼpng
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

	//������srcͬ���ͺ�ͬ��С�ľ���
	DstPic.create(image_roi.size(), img.type());

	//��ԭʼͼת��Ϊ�Ҷ�ͼ
	cvtColor(image_roi, grayImage, COLOR_BGR2GRAY);

	//��ʹ��3*3�ں�������
	blur(grayImage, edge, Size(3, 3));

	//����canny����
	Canny(edge, edge, 100, 10, 3);

	namedWindow("��Ե��ȡЧ��");
	namedWindow("�����ı�Ե��ȡЧ��");

	//��̬ѧ�˲����ղ���
	Mat kernel, dst;
	kernel = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
	morphologyEx(edge, dst, MORPH_CLOSE, kernel);
	//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	//erode(dst, dst, element);
	//dilate(dst, dst, element);

	imshow("��Ե��ȡЧ��", edge);
	imshow("�����ı�Ե��ȡЧ��", dst);

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