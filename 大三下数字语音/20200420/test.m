clc
clear

[y1,fs]=audioread('F715.wav');
figure(1);plot(y1);
title('原音频信号');
xlabel('采样点');ylabel('波形');

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
    z1=sign(y(:,i));
    if j>1
        z(j-1)=abs(z1(j)-z1(j-1));
    end
    end
    e=y(:,i);
    E(i)=sum(e.*e);%短时能量
    zs(i)=sum(z)';
    Z(i)=0.5*zs(i);%短时过零率
end
m=sum(abs(y));%短时平均幅度


figure(1);
subplot(2,1,1);plot(y1);
title('原音频信号');
xlabel('采样点');ylabel('波形');
subplot(2,1,2);plot(m);
title('短时平均幅度曲线');
xlabel('帧数');ylabel('短时平均幅度');

figure(3);plot(E);
title('短时能量曲线');
xlabel('帧数');ylabel('短时能量');

figure(4);plot(Z);
title('短时过零率');
xlabel('帧数');ylabel('短时过零率');

