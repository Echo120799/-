clc
clear

I=imread('1.jpg');
I=rgb2gray(I);
figure(1);imshow(I),title('ԭͼ');
Edge=edge(I,'sobel');
figure(2);imshow(Edge);title('��ȡ��Ե');
se=strel('square',2);
I1=imdilate(Edge,se);
imwrite(I1,'edge.png');
figure(3);imshow(I1);title('���ʹ����ı�Ե');
