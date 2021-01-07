clc
clear

I=imread('Fig0911(a).png');
subplot(1,3,1);imshow(I);title('‘≠Õº');
se=strel('square',4);
I1=imerode(I,se);
subplot(1,3,2);imshow(I1);title('œ»∏Ø ¥');
I2=imdilate(I1,se);
subplot(1,3,3);imshow(I2);title('∫Û≈Ú’Õ');
