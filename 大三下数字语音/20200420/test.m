clc
clear

[y1,fs]=audioread('F715.wav');
figure(1);plot(y1);
title('ԭ��Ƶ�ź�');
xlabel('������');ylabel('����');

len=length(y1);%�ܳ���
t=len/fs;%��ʱ��
len_frame=0.01;%֡��
len1_frame=0.2*len_frame;%֡��
N=floor(len_frame*fs);%ÿ֡�Ĳ�������
M=floor(len1_frame*fs);%֡����������
num_frame=floor((len-N)/(N-M));
for i=1:1:num_frame%��֡
    for j=1:1:N
    y(j,i)=[y1((i-1)*(N-M)+j)];
    z1=sign(y(:,i));
    if j>1
        z(j-1)=abs(z1(j)-z1(j-1));
    end
    end
    e=y(:,i);
    E(i)=sum(e.*e);%��ʱ����
    zs(i)=sum(z)';
    Z(i)=0.5*zs(i);%��ʱ������
end
m=sum(abs(y));%��ʱƽ������


figure(1);
subplot(2,1,1);plot(y1);
title('ԭ��Ƶ�ź�');
xlabel('������');ylabel('����');
subplot(2,1,2);plot(m);
title('��ʱƽ����������');
xlabel('֡��');ylabel('��ʱƽ������');

figure(3);plot(E);
title('��ʱ��������');
xlabel('֡��');ylabel('��ʱ����');

figure(4);plot(Z);
title('��ʱ������');
xlabel('֡��');ylabel('��ʱ������');

