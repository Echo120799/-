clc
clear

[y1,fs]=audioread('F715.wav');
subplot(2,1,1);plot(y1);
title('ԭ��Ƶ�ź�');
xlabel('������');ylabel('����');

len=length(y1);%�ܳ���
t=len/fs;%��ʱ��
len_frame=0.01;%֡��
len1_frame=0.2*len_frame;%֡��
N=floor(len_frame*fs);%ÿ֡�Ĳ�������
M=floor(len1_frame*fs);%֡����������
num_frame=floor((len-N)/(N-M));%֡��
for i=1:1:num_frame%��֡
    for j=1:1:N
    y(j,i)=[y1((i-1)*(N-M)+j)];
    end
end

for i=1:1:num_frame%��֡
   y_ham(:,i)=ham(y(:,i),N);
   Nfft=pow2(floor(log2(N)));
   fft1=fft(y_ham(:,i),Nfft);
   P(:,i)=abs(fft1(1:Nfft/2)).^2/(t/num_frame);
end
P= 10 * log10(P);
subplot(2,1,2);imagesc(P);
title('����ͼ');
xlabel('֡��');ylabel('Ƶ��');