clc
clear
%读取含水印图片
ImgWm=imread('picture/watermark.bmp');
ImgWm_source=reshape(ImgWm',[],1);
[m,n]=size(ImgWm);
q=32;
for i=0:m/8-1
    for j=0:n/8-1
        block=ImgWm((i*8+1:(i+1)*8),(j*8+1:(j+1)*8));%把图片划分成8*8大小的分块
        block_dct=dct2(block);%对每个分块做DCT变换
        R=mod(block_dct(1,1),q);
        if R<q/2
          watermark(i*m/8+j+1)=0;%水印为0
        else
          watermark(i*m/8+j+1)=1;%水印为1
        end
    end
end   
message = imread('picture/water.bmp');  %载入原始水印
[a,b]=size(message);
watermark_reshape=reshape(watermark,[a,b]);
imshow(watermark_reshape);title('提取出的水印图片');
imwrite(watermark_reshape,'picture/water_out.bmp');
%将提取出的水印图像转化为信息
string = repic(watermark_reshape)