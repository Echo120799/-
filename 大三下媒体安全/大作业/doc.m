clc
clear

I=imread('lena.jpg');
[cA,cH,cV,cD]=dwt2(I,'Haar');
subplot(2,2,1);imshow(uint8(cA));title('����ϵ��');
subplot(2,2,2);imshow(uint8(cH));title('ˮƽϸ�ڷ���');
subplot(2,2,3);imshow(uint8(cV));title('��ֱϸ�ڷ���');
subplot(2,2,4);imshow(uint8(cD));title('�Խ�ϸ�ڷ���');