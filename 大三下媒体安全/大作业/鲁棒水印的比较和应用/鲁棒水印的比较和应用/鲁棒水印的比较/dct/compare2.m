clc
clear
%读取原图
I=imread('picture/lena.jpg');
%改变图片尺寸
I1=imresize(I,[256,256]);
I2=imresize(I,[128,128]);

%对512*512图像加入水印
[psnr1,ssim1,ImgWm1]=DCTEmbed(I);
subplot(1,3,1);imshow(ImgWm1);title('512*512灰度图加入水印后的图像')
imwrite(ImgWm1,'compare2/watermarked1.bmp');

%对256*256图像加入水印
[psnr2,ssim2,ImgWm2]=DCTEmbed(I1);
subplot(1,3,2);imshow(ImgWm2);title('256*256灰度图加入水印后的图像')
imwrite(ImgWm2,'compare2/watermarked2.bmp');

%对128*128图像加入水印
[psnr3,ssim3,ImgWm3]=DCTEmbed(I2);
subplot(1,3,3);imshow(ImgWm3);title('128*128灰度图加入水印后的图像')
imwrite(ImgWm3,'compare2/watermarked3.bmp');