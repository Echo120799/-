clc;
clear;
I=imread('picture/lena.jpg');  %����ԭʼ����ͼ�� 
[m,n]=size(I);

%����ˮӡͼƬ
str=input('������������Ϣ:','s');
message=pic(str);

%��ˮӡ�����1*��������ʽ
message_reshape=reshape(message,1,[]);

%ģֵ
q=32;
for i=0:m/8-1
    for j=0:n/8-1
        block=I((i*8+1:(i+1)*8),(j*8+1:(j+1)*8));%��ͼƬ���ֳ�8*8��С�ķֿ�
        block_dct=dct2(block);%��ÿ���ֿ���DCT�任
        Z=mod(block_dct,q);
        k=message_reshape(i*m/8+j+1);
        if k==0%ˮӡ��Ӧ��bitλΪ0
                block_dct(1,1)=block_dct(1,1)-Z(1,1)+q/4;
            
        else%ˮӡ��Ӧ��bitλΪ1
                block_dct(1,1)=block_dct(1,1)-Z(1,1)+3*q/4;
        end
        ImgWm((i*8+1:(i+1)*8),(j*8+1:(j+1)*8))=idct2(block_dct);%��ÿ���ֿ���DCT��任
    end
end
ImgWm=uint8(ImgWm);
psnr=PSNR(ImgWm,I);
ssim=SSIM(ImgWm,I);
figure;
imshow(ImgWm);title('�Ҷ�ͼ����ˮӡ���ͼ��')
imwrite(ImgWm,'picture/watermark.bmp');