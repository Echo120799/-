clc
clear

[y1,fs]=audioread('F715.wav');
len=length(y1);%总长度
t=len/fs;%总时长
len_frame=0.01;%帧长
len1_frame=0.2*len_frame;%帧叠
N=floor(len_frame*fs);%每帧的采样点数
M=floor(len1_frame*fs);%帧叠采样点数
num_frame=floor((len-N)/(N-M));
for i=1:(N-M):num_frame
    for j=1:1:N
        y(i,j)=y1((i-1)*(N-M)+j);
    end
end
