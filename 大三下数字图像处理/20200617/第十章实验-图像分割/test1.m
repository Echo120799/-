clc
clear

I=imread('Fig10.10(a).jpg');
subplot(3,2,1);imshow(I);title('原图');
f1=fspecial('average',[5,5]);
I1=imfilter(I,f1);
subplot(3,2,2);imshow(I1);title('5*5算术均值');
bw1=edge(I1,'sobel');
subplot(3,2,3);imshow(bw1);title('sobel边缘');
bw2=edge(I1,'canny');
subplot(3,2,4);imshow(bw2);title('canny边缘');