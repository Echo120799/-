clc
clear

%读取音频文件
[y1,fs]=audioread('F715.wav');
%原音频采样点数
N=length(y1);
%原始频谱
f=fs*(0:N/2)/N;
%将原始频谱转换为mel频谱
mel=2595*log(1+f/700);
%画图
figure(1);plot(f,mel);xlabel('原频谱');ylabel('对应的mel频谱');title('两种频谱的对应曲线');

t=N/fs;%音频总时长
len_frame=0.01;%定义每一帧的时长
len1_frame=0.2*len_frame;%帧叠
n=floor(len_frame*fs);%每帧的采样点数
m=floor(len1_frame*fs);%帧叠采样点数
num_frame=floor((N-n)/(n-m));%帧数
for i=1:num_frame
    for j=1:n
    y(j,i)=[y1((i-1)*(n-m)+j)];%分帧
    end
    y2(:,i)=ham(y(:,i),n);%加汉明窗
    nfft=pow2(floor(log2(n)));
    y2_fft(:,i)=fft(y2(:,i),nfft);%fft变换
    mel2(:,i)=frq2mel(abs(y2_fft(1:nfft/2,i)));%mel频谱变换
    mel3(:,i)=log(mel2(:,i));%取对数
    mel_dct(:,i)=idct(mel3(:,i));%做逆dct变换
end
mel4=mel_dct(1:17,1:num_frame);%17维梅尔倒谱系数
figure(2);imagesc(mel4);title('mel倒谱语谱图')%画图


