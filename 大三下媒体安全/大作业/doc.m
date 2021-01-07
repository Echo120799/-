clc
clear

I=imread('lena.jpg');
[cA,cH,cV,cD]=dwt2(I,'Haar');
subplot(2,2,1);imshow(uint8(cA));title('近似系数');
subplot(2,2,2);imshow(uint8(cH));title('水平细节分量');
subplot(2,2,3);imshow(uint8(cV));title('垂直细节分量');
subplot(2,2,4);imshow(uint8(cD));title('对角细节分量');