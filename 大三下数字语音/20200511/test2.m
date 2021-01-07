clc
clear

[y1,fs]=audioread('F715.wav');
subplot(2,1,1);plot(y1);
title('原音频信号');
xlabel('采样点');ylabel('波形');

len=length(y1);%总长度
t=len/fs;%总时长
len_frame=0.01;%帧长
len1_frame=0.2*len_frame;%帧叠
N=floor(len_frame*fs);%每帧的采样点数
M=floor(len1_frame*fs);%帧叠采样点数
num_frame=floor((len-N)/(N-M));%帧数
for i=1:1:num_frame%分帧
    for j=1:1:N
    y(j,i)=[y1((i-1)*(N-M)+j)];
    end
end

for i=1:1:num_frame%分帧
   y_ham(:,i)=ham(y(:,i),N);
   Nfft=pow2(floor(log2(N)));
   fft1=fft(y_ham(:,i),Nfft);
   P(:,i)=abs(fft1(1:Nfft/2)).^2/(t/num_frame);
end
P= 10 * log10(P);
subplot(2,1,2);imagesc(P);
title('语谱图');
xlabel('帧数');ylabel('频率');