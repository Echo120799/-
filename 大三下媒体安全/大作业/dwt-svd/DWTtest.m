 clc
 clear all
 
 Img=imread('lena.jpg');  %����ԭʼ����ͼ�� 
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
Img_W=uint8(k2);   %��������ת��
figure(1);
imshow(Img_W); 
title('Ƕ��ˮӡ���ͼ��');%��ʾǶ��ˮӡ���ͼ��
imwrite(Img_W,'DWTWm.bmp');  %����Ƕ��ˮӡ���ͼ��

%����PSNR
psnr=PSNR(Img_W,Img),
ssim=SSIM(Img_W,Img),

