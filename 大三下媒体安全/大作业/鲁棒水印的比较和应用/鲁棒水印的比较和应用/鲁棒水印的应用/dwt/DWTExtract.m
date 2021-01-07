
clc
clear 

%读入嵌入水印后的图像
ImgWm=imread('picture/watermarked.bmp');  %读取未被攻击的含水印图像

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
imwrite(watermark,'picture/water_out.jpg');


%将提取的水印图片变为字符信息
string = repic(watermark)
