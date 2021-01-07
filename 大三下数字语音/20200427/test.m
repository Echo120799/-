clc
clear

[y1,fs]=audioread('F715.wav');
% figure(1);plot(y1);
% title('ԭ��Ƶ�ź�');
% xlabel('������');ylabel('����');

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
    end
end

x=ones(N,1);
y2=ham(x,N);
y3=han(x,N);
figure(1);
plot(y2,'r');hold on;
plot(y3,'b');hold on;
legend('������','������');
xlabel('������');ylabel('����');

for i=1:1:num_frame%ÿһ֡
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
title('ԭ��Ƶ�ź�');
xlabel('������');ylabel('����');
subplot(6,1,2);plot( yy(:,1));
subplot(6,1,3);plot( yy(:,2));
subplot(6,1,4);plot( yy(:,3));
subplot(6,1,5);plot( yy(:,4));
subplot(6,1,6);plot( yy(:,5));

