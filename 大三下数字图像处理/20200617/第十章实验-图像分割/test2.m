clc
clear

I=imread('Fig1039(a).tif');
subplot(1,2,1);imshow(I);title('ԭͼ');
level = graythresh(I);
bw=im2bw(I,level);
subplot(1,2,2);imshow(bw);title('�ָ�ͼ');