clc
clear

[y1,fs]=audioread('F715.wav');
len=length(y1);%�ܳ���
t=len/fs;%��ʱ��
len_frame=0.01;%֡��
len1_frame=0.2*len_frame;%֡��
N=floor(len_frame*fs);%ÿ֡�Ĳ�������
M=floor(len1_frame*fs);%֡����������
num_frame=floor((len-N)/(N-M));
for i=1:(N-M):num_frame
    for j=1:1:N
        y(i,j)=y1((i-1)*(N-M)+j);
    end
end
