clc
clear

src=zeros(512,512);
src(256-10:256+10,256-20:256+20)=255;
subplot(2,2,1);imshow(src);title('生成的图片')
imwrite(src,'test.bmp');
I=imread('test.bmp');
subplot(2,2,2);imshow(I);title('读取的图片')

F=fft2(I);
F1=fftshift(F);
F2=im2double(F1);
s=uint8(abs(F2));
subplot(2,2,3);imshow(s,[]);title('0-255')
s1=log(1+abs(F2));
subplot(2,2,4);imshow(s1,[]);title('对数变换')