 clc
 clear all
 
 Img=imread('lena.jpg');  %读入原始载体图像 
 Img=im2double(Img);
 [cA,cH,cV,cD]=dwt2(Img,'Haar');
 [cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');
 message=imread('cuc.jpg');
 message=imresize(message,2);
message=im2double(message);
[U,S,V]=svd(cA1);
k=im2double(message);
WM=S+0.005*k;
cA2=U*WM*V';
mmm=cA1-cA2;

k1=idwt2(cA2,cH1,cV1,cD1,'Haar');
k2=idwt2(k1,cH,cV,cD,'Haar');
Img_W=uint8(k2);   %数据类型转换
figure(1);
imshow(Img_W); 
title('嵌入水印后的图像');%显示嵌入水印后的图像
imwrite(Img_W,'DWTWm.bmp');  %保存嵌入水印后的图像

%计算PSNR
psnr=PSNR(Img_W,Img),
ssim=SSIM(Img_W,Img),

