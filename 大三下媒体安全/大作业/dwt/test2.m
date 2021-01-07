
clc
clear 


%读入嵌入水印后的图像
ImgWm=imread('watermarked.jpg');  %读取未被攻击的含水印图像

%%{  
%*** 对含水印图像进行JPEG压缩
%imwrite(ImgWm,'JPEG_attack.bmp','jpeg','Quality',55); 
%     %最后的这个参数为压缩强度，其值越大压缩程度越小，提取出的水印效果越好；
%     %本次实验加噪强度调节范围为30：5：60值，其中强度为49、50、51的地方有畸变，所以用48、52的中间值代替，个人选择4.814。
%     %强度大于60的其BER均为0
%ImgWm=imread('JPEG_attack.bmp');
%}

%
%*** 对含水印图像进行加噪声
%ImgWm=imnoise(ImgWm,'salt & pepper',0.006);  %椒盐噪声'salt & pepper'，本次实验加噪强度调节范围0:：0.001：0.006
%imwrite(ImgWm,'noise_attack.jpg');
%

%
%*** 对含水印图像进行旋转
ImgWm=imrotate(ImgWm,0.05,'bilinear','crop');  %第二个参数为旋转强度，可以调节,本次实验调节范围为：0：0.01：0.1
imwrite(ImgWm,'rotate_attack.jpg');
%
%三阶DWT变换
[cA,cH,cV,cD]=dwt2(ImgWm,'Haar');
[cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');
[cA2,cH2,cV2,cD2]=dwt2(cA1,'Haar');
[m,n]=size(cA2);
%模值
q=32;
R=mod(cA2,q);
for i=1:m
    for j=1:n
    if R(i,j)>q/2
        watermark(i,j)=1;%水印为1
    else
        watermark(i,j)=0;%水印为0
    end
    end
end
imshow(watermark);title('提取出的水印图片');
imwrite(watermark,'water_rotate.jpg');

%载入原始水印信息
message=imread('cuc.jpg'); 
message=uint8(fix(double(message)./128));     %将商标图变为0、1二值

%显示提取错误比特的比例
message_reshape=reshape(message,1,[]);
watermark_reshape=reshape(watermark,1,[]);
BER=sum(abs(double(message_reshape)-watermark_reshape))/(m*n),

