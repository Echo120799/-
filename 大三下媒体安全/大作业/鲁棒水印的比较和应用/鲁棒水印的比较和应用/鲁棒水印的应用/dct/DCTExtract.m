clc
clear
%��ȡ��ˮӡͼƬ
ImgWm=imread('picture/watermark.bmp');
ImgWm_source=reshape(ImgWm',[],1);
[m,n]=size(ImgWm);
q=32;
for i=0:m/8-1
    for j=0:n/8-1
        block=ImgWm((i*8+1:(i+1)*8),(j*8+1:(j+1)*8));%��ͼƬ���ֳ�8*8��С�ķֿ�
        block_dct=dct2(block);%��ÿ���ֿ���DCT�任
        R=mod(block_dct(1,1),q);
        if R<q/2
          watermark(i*m/8+j+1)=0;%ˮӡΪ0
        else
          watermark(i*m/8+j+1)=1;%ˮӡΪ1
        end
    end
end   
message = imread('picture/water.bmp');  %����ԭʼˮӡ
[a,b]=size(message);
watermark_reshape=reshape(watermark,[a,b]);
imshow(watermark_reshape);title('��ȡ����ˮӡͼƬ');
imwrite(watermark_reshape,'picture/water_out.bmp');
%����ȡ����ˮӡͼ��ת��Ϊ��Ϣ
string = repic(watermark_reshape)