
fs=1200;
[y1,fs]=audioread('F2515.wav');
subplot(4,1,1);plot(y1);
title('����ͼ');
xlabel('Ƶ��');ylabel('����');

[y2,fs]=audioread('F2516.wav');
subplot(4,1,2);plot(y2);
title('����ͼ');
xlabel('Ƶ��');ylabel('����');

[y3,fs]=audioread('F2517.wav');
subplot(4,1,3);plot(y3);
title('����ͼ');
xlabel('Ƶ��');ylabel('����');

[y4,fs]=audioread('F2518.wav');
subplot(4,1,4);plot(y4);
title('����ͼ');
xlabel('Ƶ��');ylabel('����');
