clc
clear
%读取原图
I=imread('lena.jpg');
%一阶DWT变换
[cA,cH,cV,cD]=dwt2(I,'Haar');
%选取低频分量cA进行后续操作
[m,n]=size(cA);
%读取水印
message=imread('cuc.jpg');
message=uint8(fix(double(message)./128));     %将商标图变为0、1二值
%str=input('请输入隐藏信息:','s');
%message=pic(str);
%将水印处理为1*【】的形式
message_reshape=reshape(message,1,[]);
q=32;%嵌入强度
for i=0:m/4-1
    for j=0:n/4-1
        block=cA((i*4+1:(i+1)*4),(j*4+1:(j+1)*4));%把低频分量cA划分成4*4大小的分块
        [U,S,V]=svd(block);%对每一个分块进行奇异值分解
        Z=mod(S(1,1),q);%S（1,1）：每一个分块奇异值矩阵的第一个元素，即最大奇异值
        k=message_reshape(i*m/4+j+1);
        if k==0%水印对应的bit位为0
            if Z>3*q/4
                S1=S(1,1)-Z+5*q/4;
            else
                S1=S(1,1)-Z+q/4;
            end
        else%水印对应的bit位为1
             if Z>q/4
                S1=S(1,1)-Z+3*q/4;
            else
                S1=S(1,1)-Z-q/4;
             end
        end
        S2=S;
        S2(1,1)=S1;
        block1=U*S2*V';%还原分块
        watermark((i*4+1:(i+1)*4),(j*4+1:(j+1)*4))=block1;%分块组成处理过的低频分量
    end
end
ImgWm=idwt2(watermark,cH,cV,cD,'Haar');%DWT逆变换
ImgWm=uint8(ImgWm);
imshow(ImgWm);title('加入水印后的图像')
imwrite(ImgWm,'watermarked.jpg');
%计算PSNR
psnr=PSNR(ImgWm,I),
ssim=SSIM(ImgWm,I),

