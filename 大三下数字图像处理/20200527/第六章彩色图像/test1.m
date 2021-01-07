clc
clear

src=imread('Fig0637(a).tif');
R=src(:,:,1);
G=src(:,:,2);
B=src(:,:,3);
src_gray=rgb2gray(src);
figure(1);subplot(2,3,1);imshow(src);title('ԭͼ');
subplot(2,3,2);imshow(src_gray);title('ԭͼ�Ҷ�ͼ');
subplot(2,3,3);imshow(R);title('Rͨ��');
subplot(2,3,4);imshow(G);title('Gͨ��');
subplot(2,3,5);imshow(B);title('Bͨ��');

src_hsi=rgb2hsi(src);
H=src(:,:,1);
S=src(:,:,2);
I=src(:,:,3);
figure(2);subplot(2,2,1);imshow(src_hsi);title('HSIͼ');
subplot(2,2,2);imshow(H);title('Hͨ��');
subplot(2,2,3);imshow(S);title('Sͨ��');
subplot(2,2,4);imshow(I);title('Iͨ��');


I_hist=imhist(I);
I_J=histeq(I);
I_J_hist=imhist(I_J);
figure(3);subplot(2,2,1);imshow(I);title('Iͨ��');
subplot(2,2,2);plot(I_hist);title('Iͨ��ԭʼֱ��ͼ');
subplot(2,2,3);imshow(I_J);title('Iͨ�������');
subplot(2,2,4);plot(I_J_hist);title('Iͨ�������ֱ��ͼ');

H_J=histeq(H);
S_J=histeq(S);
HSI_1=cat(3,H_J,S_J,I_J);
%RGB1=hsi2rgb(src_hsi);
figure(4);imshow(HSI_1);title('�����ͼ��');