clc
clear

%��ȡ��Ƶ�ļ�
[y1,fs]=audioread('F715.wav');
%ԭ��Ƶ��������
N=length(y1);
%ԭʼƵ��
f=fs*(0:N/2)/N;
%��ԭʼƵ��ת��ΪmelƵ��
mel=2595*log(1+f/700);
%��ͼ
figure(1);plot(f,mel);xlabel('ԭƵ��');ylabel('��Ӧ��melƵ��');title('����Ƶ�׵Ķ�Ӧ����');

t=N/fs;%��Ƶ��ʱ��
len_frame=0.01;%����ÿһ֡��ʱ��
len1_frame=0.2*len_frame;%֡��
n=floor(len_frame*fs);%ÿ֡�Ĳ�������
m=floor(len1_frame*fs);%֡����������
num_frame=floor((N-n)/(n-m));%֡��
for i=1:num_frame
    for j=1:n
    y(j,i)=[y1((i-1)*(n-m)+j)];%��֡
    end
    y2(:,i)=ham(y(:,i),n);%�Ӻ�����
    nfft=pow2(floor(log2(n)));
    y2_fft(:,i)=fft(y2(:,i),nfft);%fft�任
    mel2(:,i)=frq2mel(abs(y2_fft(1:nfft/2,i)));%melƵ�ױ任
    mel3(:,i)=log(mel2(:,i));%ȡ����
    mel_dct(:,i)=idct(mel3(:,i));%����dct�任
end
mel4=mel_dct(1:17,1:num_frame);%17ά÷������ϵ��
figure(2);imagesc(mel4);title('mel��������ͼ')%��ͼ


