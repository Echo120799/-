%************* DWT域熵掩蔽模型水印算法-提取
clc
clear all;
close all;

%读入嵌入水印后的图像
ImgWm=imread('DWTWm.bmp');  %读取未被攻击的含水印图像
[ca,ch,cv,cd]=dwt2(ImgWm,'Haar');
[ca1,ch1,cv1,cd1]=dwt2(ca,'Haar');

[u,s,v]=svd(ca1);

Img=imread('lena.jpg');  %读入原始载体图像 
[cA,cH,cV,cD]=dwt2(Img,'Haar');
[cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');

[U,S,V]=svd(cA1);
 
WM=s-S;
imshow(WM);



 

