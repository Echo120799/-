clc
clear

[y1,fs]=audioread('F715.wav');
len=length(y1);%�ܳ���
t=len/fs;%��ʱ��
len_frame=0.01;%֡��
len1_frame=0.2*len_frame;%֡��
N=floor(len_frame*fs);%ÿ֡�Ĳ�������
M=floor(len1_frame*fs);%֡����������
num_frame=floor((len-N)/(N-M));%֡��
Nfft=pow2(floor(log2(N)));
for i=1:1:num_frame%��֡
    for j=1:1:N
    y(j,i)=[y1((i-1)*(N-M)+j)];
   
% plot(fft1);
    end
    %fft(:,i)=fft(y(:,i),Nfft);
end
fft(:,1)=fft(y(:,1),Nfft);
figure(1);plot(abs(fft(1:Nfft/2,1)));
mel=frq2mel(fft(1:Nfft/2,1));
figure(2);plot(abs(mel));%melϵ��
% mmm=2595*log10(1+fft(1:Nfft/2,1)/700);
% figure(3);plot(abs(mmm));%melϵ��
mel2=log(mel);
%figure(3);plot(abs(mel2));
t=mel2(2:13);
x=idct(t);
figure(3);plot(abs(x));