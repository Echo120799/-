 clc
 clear
 
 I=imread('picture/lena.jpg');  %读入原始载体图像 
 %三阶DWT变换
 [cA,cH,cV,cD]=dwt2(I,'Haar');
 [cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');
 [cA2,cH2,cV2,cD2]=dwt2(cA1,'Haar');

 %生成水印图片

 str=input('请输入隐藏信息:','s');
 message=pic(str);
 [m,n]=size(cA2);
 
 %模值
 q=32;
 Z=mod(cA2,q);

 %对低频分量进行处理
for i=1:m
    for j=1:n
        if message(i,j)==0%对应位置水印值为0
            if Z(i,j)>3*q/4
                cA2(i,j)=cA2(i,j)-Z(i,j)+5*q/4;
            else
                cA2(i,j)=cA2(i,j)-Z(i,j)+q/4;
            end
        else%对应位置水印值为1
             if Z(i,j)>q/4
                cA2(i,j)=cA2(i,j)-Z(i,j)+3*q/4;
            else
                cA2(i,j)=cA2(i,j)-Z(i,j)-q/4;
            end
        end
    end
end
%三阶DWT逆变换
k1=idwt2(cA2,cH2,cV2,cD2,'Haar');
k2=idwt2(k1,cH1,cV1,cD1,'Haar');
k3=idwt2(k2,cH,cV,cD,'Haar');
ImgWm=uint8(k3);   %数据类型转换
figure;
imshow(ImgWm); title('加入水印后的图像');
imwrite(ImgWm,'picture/watermarked.bmp'); 

%计算PSNR
psnr=PSNR(ImgWm,I),
ssim=SSIM(ImgWm,I),

