clc
clear

I=imread('Fig10.10(a).jpg');
subplot(3,2,1);imshow(I);title('ԭͼ');
f1=fspecial('average',[5,5]);
I1=imfilter(I,f1);
subplot(3,2,2);imshow(I1);title('5*5������ֵ');
bw1=edge(I1,'sobel');
subplot(3,2,3);imshow(bw1);title('sobel��Ե');
bw2=edge(I1,'canny');
subplot(3,2,4);imshow(bw2);title('canny��Ե');