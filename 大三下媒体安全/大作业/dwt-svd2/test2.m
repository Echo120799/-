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
%ImgWm=imrotate(ImgWm,0.05,'bilinear','crop');  %第二个参数为旋转强度，可以调节,本次实验调节范围为：0：0.01：0.1

%对含水印图像进行DWT变换
[LL,LH,HL,HH]=dwt2(ImgWm,'Haar');
[m,n]=size(LL);
%number_block=(m/4)*(n/4);
q=32;
for i=0:m/4-1
    for j=0:n/4-1
        block=LL((i*4+1:(i+1)*4),(j*4+1:(j+1)*4));
        [U,S,V]=svd(block);
        R=mod(S(1,1),q);
        if R<q/2
          watermark(i*64+j+1)=0;
        else
          watermark(i*64+j+1)=1;
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
imwrite(watermark_reshape,'water_rotate.jpg');
%显示提取错误比特的比例
message_reshape=reshape(message,1,[]);
BER=sum(abs(double(message_reshape)-watermark))/(a*b),



