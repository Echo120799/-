clc
clear
%��ȡԭͼ
I=imread('picture/lena.jpg');
%�ı�ͼƬ�ߴ�
I1=imresize(I,[256,256]);
I2=imresize(I,[128,128]);

%��512*512ͼ�����ˮӡ
[psnr1,ssim1,ImgWm1]=DCTEmbed(I);
subplot(1,3,1);imshow(ImgWm1);title('512*512�Ҷ�ͼ����ˮӡ���ͼ��')
imwrite(ImgWm1,'compare2/watermarked1.bmp');

%��256*256ͼ�����ˮӡ
[psnr2,ssim2,ImgWm2]=DCTEmbed(I1);
subplot(1,3,2);imshow(ImgWm2);title('256*256�Ҷ�ͼ����ˮӡ���ͼ��')
imwrite(ImgWm2,'compare2/watermarked2.bmp');

%��128*128ͼ�����ˮӡ
[psnr3,ssim3,ImgWm3]=DCTEmbed(I2);
subplot(1,3,3);imshow(ImgWm3);title('128*128�Ҷ�ͼ����ˮӡ���ͼ��')
imwrite(ImgWm3,'compare2/watermarked3.bmp');