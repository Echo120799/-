clc
clear

[y,fs]=audioread('F715.wav');
len=length(y);
t=len/fs;%总时长
y1=rect(y,len);
y2=ham(y,len);
y3=han(y,len);
N=pow2(floor(log2(len)));
fft1=fft(y1,N);
fft2=fft(y2,N);
fft3=fft(y3,N);
len1=round(N/2);

P1=abs(fft1(1:len1)).^2/t;
P2=abs(fft2(1:len1)).^2/t;
P3=abs(fft3(1:len1)).^2/t;

figure(1);
subplot(3,1,1);plot(P1);
title('矩形窗');

subplot(3,1,2);plot(P2);
title('汉明窗');

subplot(3,1,3);plot(P3);
title('汉宁窗');
