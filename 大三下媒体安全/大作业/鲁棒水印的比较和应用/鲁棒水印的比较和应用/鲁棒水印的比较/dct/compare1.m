clc
clear
%读取原图
I_rgb=imread('picture/lena_rgb.jpg');
%1.灰度图（单通道）
I = rgb2gray(I_rgb);
%2.R,G,B三通道
R = I_rgb(:,:,1);%R通道
G = I_rgb(:,:,2);%G通道
B = I_rgb(:,:,3);%B通道

%对灰度图加入水印
[psnrI,ssimI,ImgWmI]=DCTEmbed(I);
subplot(2,2,1);imshow(ImgWmI);title('灰度图加入水印后的图像')
imwrite(ImgWmI,'compare1/watermarkedI.bmp');

%对R通道加入水印
[psnrR,ssimR,ImgWmR]=DCTEmbed(R);
subplot(2,2,2);imshow(ImgWmR);title('R通道图加入水印后的图像')
imwrite(ImgWmR,'compare1/watermarkedR.bmp');

%对G通道加入水印
[psnrG,ssimG,ImgWmG]=DCTEmbed(G);
subplot(2,2,3);imshow(ImgWmG);title('G通道图加入水印后的图像')
imwrite(ImgWmG,'compare1/watermarkedG.bmp');

%对B通道加入水印
[psnrB,ssimB,ImgWmB]=DCTEmbed(B);
subplot(2,2,4);imshow(ImgWmB);title('B通道图加入水印后的图像')
imwrite(ImgWmB,'compare1/watermarkedB.bmp');
