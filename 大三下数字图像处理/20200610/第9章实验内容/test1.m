clc
clear

I=imread('Fig0911(a).png');
subplot(1,3,1);imshow(I);title('ԭͼ');
se=strel('square',4);
I1=imerode(I,se);
subplot(1,3,2);imshow(I1);title('�ȸ�ʴ');
I2=imdilate(I1,se);
subplot(1,3,3);imshow(I2);title('������');
