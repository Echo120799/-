clc
clear
%读取原图
I=imread('lena.jpg');
[m,n]=size(I);
%读取水印图片
message=imread('cuc.jpg');
message=uint8(fix(double(message)./128));     %将商标图变为0、1二值
%str=input('请输入隐藏信息:','s');
%message=pic(str);
%把水印处理成1*【】的形式
message_reshape=reshape(message,1,[]);

%模值
q=32;
for i=0:m/8-1
    for j=0:n/8-1
        block=I((i*8+1:(i+1)*8),(j*8+1:(j+1)*8));%把图片划分成8*8大小的分块
        block_dct=dct2(block);%对每个分块做DCT变换
        Z=mod(block_dct,q);
        k=message_reshape(i*m/8+j+1);
        if k==0%水印对应的bit位为0
                block_dct(1,1)=block_dct(1,1)-Z(1,1)+q/4;
            
        else%水印对应的bit位为1
                block_dct(1,1)=block_dct(1,1)-Z(1,1)+3*q/4;
        end
        ImgWm((i*8+1:(i+1)*8),(j*8+1:(j+1)*8))=idct2(block_dct);%对每个分块做DCT逆变换
    end
end
ImgWm=uint8(ImgWm);
imshow(ImgWm);title('加入水印后的图像')
imwrite(ImgWm,'watermarked.jpg');
psnr=PSNR(ImgWm,I),
ssim=SSIM(ImgWm,I),

