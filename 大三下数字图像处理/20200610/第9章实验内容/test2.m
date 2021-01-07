clc
clear

I=imread('1.jpg');
I=rgb2gray(I);
figure(1);imshow(I),title('原图');
Edge=edge(I,'sobel');
figure(2);imshow(Edge);title('提取边缘');
se=strel('square',2);
I1=imdilate(Edge,se);
imwrite(I1,'edge.png');
figure(3);imshow(I1);title('膨胀处理后的边缘');
