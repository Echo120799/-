clc
clear

I=imread('lena.jpg');
[m,n]=size(I);
%figure(1);imshow(I);title('ԭͼ');
for k=1:8
 for i=1:m
     for j=1:n
      tmp(i,j) = bitget(I(i,j),k);%bitget�������Ƚ�X(i,j)���Ҷ�ֵ�ֽ�Ϊ�����ƴ���Ȼ��ȡ��kλ
     end
 end
 ind = num2str(k);
 %img(:,:,k)=tmp;
 %figure(k+1);imshow(tmp,[]);imti = ['��',ind,'��λƽ��'];title(imti);
end
%����ˮӡͼ��
message=imread('cuc.jpg');
message=double(message);
message=round(message./256);
message=uint8(message);
%figure(1);imshow(message);
[mm,nn]=size(message);
%��ˮӡ��չΪԭͼ���С����д��watermark
for i = 1:m
     for j = 1:n
         p(i,j)=message(mod(i, mm)+1,mod(j, nn)+1);
     end
end


for k=1:8
    for i = 1:m
         for j = 1:n
            img(i,j,k)=bitset(I(i, j), k, p(i ,j));
            
         end 
    end
end
%imwrite(watermarked_image,'lsb_watermarked.bmp','bmp');
% figure(2);imshow(img(:,:,1));
% psnr=PSNR(I, img(:,:,1)),
% ssim=SSIM(I, img(:,:,1)),

r=img(:,:,8);
for i = 1:m
   for j = 1:n
       q(i,j)=bitget(r(i,j),8);
   end
end
q=256*double(q);
%����ȡˮӡ��Ϊԭʼˮӡ��С
for ii = 1:mm-1
    for jj = 1:nn-1
        watermark1(ii+1,jj+1)=q(ii,jj);
    end
end
watermark1(1,1)=q(mm,nn);

II=imread('cuc.jpg');
message_pad=double(II);
message_pad=round(message_pad./256);
message_pad=uint8(message_pad);
message_pad=reshape(message_pad,[1,64*64]);

message_pad_recover=double(watermark1);
message_pad_recover=round(message_pad_recover./256);
message_pad_recover=uint8(message_pad_recover);
message_pad_recover=reshape(message_pad_recover,[1,64*64]);

% ��ʾ��ȡ������صı���

len=length(message_pad);
bit_error_rate=sum(abs(message_pad_recover(1:len)-message_pad(1:len)))/len,
