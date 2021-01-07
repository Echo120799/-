clc
clear
%读取原图
I=imread('picture/lena.jpg');
%改变图片格式
imwrite(I,'compare3/lena.bmp');
imwrite(I,'compare3/lena.tif');
I1=imread('compare3/lena.bmp');
I2=imread('compare3/lena.tif');

%对jpg格式图像加入水印
[psnr1,ssim1,ImgWm1]=DCTEmbed(I);
subplot(1,3,1);imshow(ImgWm1);title('jpg格式加入水印后的图像')
imwrite(ImgWm1,'compare3/watermarked1.bmp');

%对bmp格式图像加入水印
[psnr2,ssim2,ImgWm2]=DCTEmbed(I1);
subplot(1,3,2);imshow(ImgWm2);title('bmp格式加入水印后的图像')
imwrite(ImgWm2,'compare3/watermarked2.bmp');

%对tif图像加入水印
[psnr3,ssim3,ImgWm3]=DCTEmbed(I2);
subplot(1,3,3);imshow(ImgWm3);title('tif格式加入水印后的图像')
imwrite(ImgWm3,'compare3/watermarked3.bmp');
