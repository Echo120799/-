clc
clear
%读取含水印图片
ImgWm=imread('watermarked.jpg');

%*** 对含水印图像进行JPEG压缩
%imwrite(ImgWm,'JPEG_attack.bmp','jpeg','Quality',55); 
    %最后的这个参数为压缩强度，其值越大压缩程度越小，提取出的水印效果越好；
    %本次实验加噪强度调节范围为30：5：60值，其中强度为49、50、51的地方有畸变，所以用48、52的中间值代替，个人选择4.814。
    %强度大于60的其BER均为0
%ImgWm=imread('JPEG_attack.bmp');
%}

%
%*** 对含水印图像进行加噪声
%ImgWm=imnoise(ImgWm,'salt & pepper',0.006);  %椒盐噪声'salt & pepper'，本次实验加噪强度调节范围0:：0.001：0.006
%

%
%*** 对含水印图像进行旋转
ImgWm=imrotate(ImgWm,0.02,'bilinear','crop');  %第二个参数为旋转强度，可以调节,本次实验调节范围为：0：0.01：0.1
[m,n]=size(ImgWm);
q=32;
for i=0:m/8-1
    for j=0:n/8-1
        block=ImgWm((i*8+1:(i+1)*8),(j*8+1:(j+1)*8));%把图片划分成8*8大小的分块
        block_dct=dct2(block);%对每个分块做DCT变换
        R=mod(block_dct(1,1),q);
        if R<q/2
          watermark(i*64+j+1)=0;%水印为0
        else
          watermark(i*64+j+1)=1;%水印为1
        end
    end
end
%读取原水印
message=imread('cuc.jpg');
 %将商标图变为0、1二值
message=uint8(fix(double(message)./128));    
[a,b]=size(message);
watermark_reshape=reshape(watermark,[a,b]);
imshow(watermark_reshape);title('提取出的水印图片');
imwrite(watermark_reshape,'picture_after.bmp')
%显示提取错误比特的比例
message_reshape=reshape(message,1,[]);
BER=sum(abs(double(message_reshape)-watermark))/(a*b),
