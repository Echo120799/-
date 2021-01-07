clc
clear

fs=1200;
[y1,fs]=audioread('F2515.wav');
subplot(3,1,1);plot(y1);
title('F2515');
%xlabel('频率');ylabel('波形');

[y2,fs]=audioread('F715.wav');
subplot(3,1,2);plot(y2);
title('F715');
%xlabel('频率');ylabel('波形');

m1=length(y1);
m2=length(y2);
for n=1:m2
    x(n,1)=y2(n,1);
end
for n=1:m1
    x(n,1)=x(n,1)+y1(n,1);
end
subplot(3,1,3);plot(x);
title('合');
%xlabel('频率');ylabel('波形');