clc
clear

[y1,fs]=audioread('F715.wav');
% figure(1);plot(y1);
% title('原音频信号');
% xlabel('采样点');ylabel('波形');

len=length(y1);%总长度
t=len/fs;%总时长
len_frame=0.01;%帧长
len1_frame=0.2*len_frame;%帧叠
N=floor(len_frame*fs);%每帧的采样点数
M=floor(len1_frame*fs);%帧叠采样点数
num_frame=floor((len-N)/(N-M));
for i=1:1:num_frame%分帧
    for j=1:1:N
    y(j,i)=[y1((i-1)*(N-M)+j)];
    end
end

x=ones(N,1);
y2=ham(x,N);
y3=han(x,N);
figure(1);
plot(y2,'r');hold on;
plot(y3,'b');hold on;
legend('汉明窗','汉宁窗');
xlabel('采样点');ylabel('波形');

for i=1:1:num_frame%每一帧
   for k=0:1:N-1
       R(k+1,i)=0;
        for m=1:1:N-k
            R(k+1,i)=R(k+1,i)+y(m,i)*y(m+k,i);
        end
    end
end
a=randint(1,5,[1 67]);
for s=1:1:5
    yy(:,s)=R(:,a(s));
end

figure(2);
subplot(6,1,1);plot(y1);
title('原音频信号');
xlabel('采样点');ylabel('波形');
subplot(6,1,2);plot( yy(:,1));
subplot(6,1,3);plot( yy(:,2));
subplot(6,1,4);plot( yy(:,3));
subplot(6,1,5);plot( yy(:,4));
subplot(6,1,6);plot( yy(:,5));

