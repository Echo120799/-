clc
clear

I=imread('Fig0918(a).tif');
BW = im2bw(I,0.8);
figure(1);imshow(BW);
se=strel('square',6);
I1=imdilate(BW,se);
figure(2);imshow(I1);title('膨胀');
se1=strel('square',4);
I2=imerode(I1,se1);
figure(3);imshow(I2);title('腐蚀');
BW2 = bwareaopen(I2,200);
figure(4);imshow(BW2);title('去除小面积');
[L, num] = bwlabel(BW2,4);
 RGB=label2rgb(L,@jet,[0 0 0]);
figure(5);imshow(RGB);title('伪彩色图像');