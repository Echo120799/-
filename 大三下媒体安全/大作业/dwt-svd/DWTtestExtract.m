%************* DWT�����ڱ�ģ��ˮӡ�㷨-��ȡ
clc
clear all;
close all;

%����Ƕ��ˮӡ���ͼ��
ImgWm=imread('DWTWm.bmp');  %��ȡδ�������ĺ�ˮӡͼ��
[ca,ch,cv,cd]=dwt2(ImgWm,'Haar');
[ca1,ch1,cv1,cd1]=dwt2(ca,'Haar');

[u,s,v]=svd(ca1);

Img=imread('lena.jpg');  %����ԭʼ����ͼ�� 
[cA,cH,cV,cD]=dwt2(Img,'Haar');
[cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');

[U,S,V]=svd(cA1);
 
WM=s-S;
imshow(WM);



 

