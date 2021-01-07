%��ˮӡ������ͼ������ȡ�������������������

clc
clear all;
close all;

%ˮӡͼ����ȡ
file_name='lsb_watermarked.bmp';
watermarked_image=imread(file_name);
Mw =size(watermarked_image,1);
Nw =size(watermarked_image,2);

%����ԭʼˮӡ
file_name='cuc.jpg';
orig_watermark=imread(file_name);
figure(1);
imshow(orig_watermark,[]);
title('orig_watermark');

message_pad=double(orig_watermark);
message_pad=round(message_pad./256);
message_pad=uint8(message_pad);
message_pad=reshape(message_pad,[1,64*64]);

%%ԭʼˮӡ������������
Mm=size(orig_watermark,1);	        %ˮӡ������
Nm=size(orig_watermark,2);	        %ˮӡ������

% ��Ƕ��ˮӡͼ��������Чλ�ؽ�ˮӡ
for ii = 1:Mw
   for jj = 1:Nw
       watermark(ii, jj)=bitget(watermarked_image(ii, jj),1);
   end
end
watermark=256*double(watermark);

%����ȡˮӡ��Ϊԭʼˮӡ��С
for ii = 1:Mm-1
    for jj = 1:Nm-1
        watermark1(ii+1,jj+1)=watermark(ii,jj);
    end
end
watermark1(1,1)=watermark(Mm,Nm);
%��ʾ��ȡ��ˮӡͼ��
figure(2);
imshow(watermark1,[]);
title('Recovered Watermark');

message_pad_recover=double(watermark1);
message_pad_recover=round(message_pad_recover./256);
message_pad_recover=uint8(message_pad_recover);
message_pad_recover=reshape(message_pad_recover,[1,64*64]);

% ��ʾ��ȡ������صı���

len=length(message_pad);
bit_error_rate=sum(abs(message_pad_recover(1:len)-message_pad(1:len)))/len,