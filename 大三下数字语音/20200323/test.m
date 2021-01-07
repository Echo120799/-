
fs=1200;
[y1,fs]=audioread('F2515.wav');
subplot(4,1,1);plot(y1);
title('波形图');
xlabel('频率');ylabel('波形');

[y2,fs]=audioread('F2516.wav');
subplot(4,1,2);plot(y2);
title('波形图');
xlabel('频率');ylabel('波形');

[y3,fs]=audioread('F2517.wav');
subplot(4,1,3);plot(y3);
title('波形图');
xlabel('频率');ylabel('波形');

[y4,fs]=audioread('F2518.wav');
subplot(4,1,4);plot(y4);
title('波形图');
xlabel('频率');ylabel('波形');
