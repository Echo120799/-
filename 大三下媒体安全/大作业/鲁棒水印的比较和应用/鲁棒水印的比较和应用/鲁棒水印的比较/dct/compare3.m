clc
clear
%��ȡԭͼ
I=imread('picture/lena.jpg');
%�ı�ͼƬ��ʽ
imwrite(I,'compare3/lena.bmp');
imwrite(I,'compare3/lena.tif');
I1=imread('compare3/lena.bmp');
I2=imread('compare3/lena.tif');

%��jpg��ʽͼ�����ˮӡ
[psnr1,ssim1,ImgWm1]=DCTEmbed(I);
subplot(1,3,1);imshow(ImgWm1);title('jpg��ʽ����ˮӡ���ͼ��')
imwrite(ImgWm1,'compare3/watermarked1.bmp');

%��bmp��ʽͼ�����ˮӡ
[psnr2,ssim2,ImgWm2]=DCTEmbed(I1);
subplot(1,3,2);imshow(ImgWm2);title('bmp��ʽ����ˮӡ���ͼ��')
imwrite(ImgWm2,'compare3/watermarked2.bmp');

%��tifͼ�����ˮӡ
[psnr3,ssim3,ImgWm3]=DCTEmbed(I2);
subplot(1,3,3);imshow(ImgWm3);title('tif��ʽ����ˮӡ���ͼ��')
imwrite(ImgWm3,'compare3/watermarked3.bmp');
