%��ˮӡͼ�����Ҫλ(LSB)����Ƕ�뵽����ͼ���У�������PSNR
clc
clear all;
close all;

% ��������ͼ��
file_name='lena.jpg';
cover_object=imread(file_name);
figure(1);
imshow(cover_object,[]);
title('ԭʼͼ��');
% ����ˮӡͼ��
file_name='cuc.jpg';
message=imread(file_name);
message=double(message);
message=round(message./256);
message=uint8(message);
% ȷ������ͼ��Ĵ�С
Mc=size(cover_object,1);
Nc=size(cover_object,2);
% ȷ��ˮӡͼ��Ĵ�С
Mm=size(message,1);
Nm=size(message,2);
% ��ˮӡ��չΪԭͼ���С����д��watermark
for ii = 1:Mc
    for jj = 1:Nc
        watermark(ii,jj)=message(mod(ii, Mm)+1,mod(jj, Nm)+1);
    end
end
% ��ԭͼ�������Чλֵ��Ϊˮӡ��ֵ
watermarked_image=cover_object;
for ii = 1:Mc
   for jj = 1:Nc
       watermarked_image(ii, jj)=bitset(watermarked_image(ii, jj), 1, watermark(ii ,jj));
   end 
end
imwrite(watermarked_image,'lsb_watermarked.bmp','bmp');

% ��ʾ��Ƕ��ˮӡ��ͼ�� 
figure(2);
imshow(watermarked_image,[]);
title('Ƕ��ˮӡ��ͼ��');

% ������Ƕ��ˮӡͼ���PSNR
psnr=PSNR(cover_object, watermarked_image),






