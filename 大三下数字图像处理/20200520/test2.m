clc
clear

src=imread('Fig0507(a)(ckt-board-orig).tif');
subplot(3,3,1);imshow(src);title('原图');
src=im2double(src);
[M,N]=size(src);
src_sp=imnoise(src,'salt & pepper',0.25);
subplot(3,3,2);imshow(src_sp);title('椒盐噪声');
src_g=imnoise(src_sp,'gaussian', 0, 0.005);
subplot(3,3,3);imshow(src_g);title('椒盐加高斯');

output1=medfilt2(src_sp,[5,5]);
subplot(3,3,4);imshow(output1);title('5*5中值');
output2=adpmedian(src_sp,9);
subplot(3,3,5);imshow(output2);title('自适应中值');

output3=spfilt(src_g, 'atrimmed', 3, 3, 2);
subplot(3,3,6);imshow(output3);
title('修正后的阿尔法均值滤波器');

f1=fspecial('average',[3,3]);
output4=imfilter(src_g,f1);
subplot(3,3,7);imshow(output4);title('3*3算术均值');

output5=exp(imfilter(log(src_g),fspecial('average',3)));
subplot(3,3,8);imshow(output5,[]);title('3*3几何均值滤波');

output6=wiener2(src_g,[10 10]);  
subplot(3,3,9);imshow(output6,[]);title('维纳滤波');
