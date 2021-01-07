clc
clear
%��ȡԭͼ
I_rgb=imread('picture/lena_rgb.jpg');
%1.�Ҷ�ͼ����ͨ����
I = rgb2gray(I_rgb);
%2.R,G,B��ͨ��
R = I_rgb(:,:,1);%Rͨ��
G = I_rgb(:,:,2);%Gͨ��
B = I_rgb(:,:,3);%Bͨ��

%�ԻҶ�ͼ����ˮӡ
[psnrI,ssimI,ImgWmI]=DCTEmbed(I);
subplot(2,2,1);imshow(ImgWmI);title('�Ҷ�ͼ����ˮӡ���ͼ��')
imwrite(ImgWmI,'compare1/watermarkedI.bmp');

%��Rͨ������ˮӡ
[psnrR,ssimR,ImgWmR]=DCTEmbed(R);
subplot(2,2,2);imshow(ImgWmR);title('Rͨ��ͼ����ˮӡ���ͼ��')
imwrite(ImgWmR,'compare1/watermarkedR.bmp');

%��Gͨ������ˮӡ
[psnrG,ssimG,ImgWmG]=DCTEmbed(G);
subplot(2,2,3);imshow(ImgWmG);title('Gͨ��ͼ����ˮӡ���ͼ��')
imwrite(ImgWmG,'compare1/watermarkedG.bmp');

%��Bͨ������ˮӡ
[psnrB,ssimB,ImgWmB]=DCTEmbed(B);
subplot(2,2,4);imshow(ImgWmB);title('Bͨ��ͼ����ˮӡ���ͼ��')
imwrite(ImgWmB,'compare1/watermarkedB.bmp');
