%将水印图像按最不重要位(LSB)方法嵌入到载体图像中，并计算PSNR
clc
clear all;
close all;

% 读入载体图像
file_name='lena.jpg';
cover_object=imread(file_name);
figure(1);
imshow(cover_object,[]);
title('原始图像');
% 读入水印图像
file_name='cuc.jpg';
message=imread(file_name);
message=double(message);
message=round(message./256);
message=uint8(message);
% 确定载体图像的大小
Mc=size(cover_object,1);
Nc=size(cover_object,2);
% 确定水印图像的大小
Mm=size(message,1);
Nm=size(message,2);
% 将水印扩展为原图像大小，并写入watermark
for ii = 1:Mc
    for jj = 1:Nc
        watermark(ii,jj)=message(mod(ii, Mm)+1,mod(jj, Nm)+1);
    end
end
% 将原图的最低有效位值换为水印的值
watermarked_image=cover_object;
for ii = 1:Mc
   for jj = 1:Nc
       watermarked_image(ii, jj)=bitset(watermarked_image(ii, jj), 1, watermark(ii ,jj));
   end 
end
imwrite(watermarked_image,'lsb_watermarked.bmp','bmp');

% 显示已嵌入水印的图像 
figure(2);
imshow(watermarked_image,[]);
title('嵌入水印后图像');

% 计算已嵌入水印图像的PSNR
psnr=PSNR(cover_object, watermarked_image),






