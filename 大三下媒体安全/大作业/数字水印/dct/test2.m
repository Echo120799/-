clc
clear
%��ȡ��ˮӡͼƬ
ImgWm=imread('watermarked.jpg');

%*** �Ժ�ˮӡͼ�����JPEGѹ��
%imwrite(ImgWm,'JPEG_attack.bmp','jpeg','Quality',55); 
    %�����������Ϊѹ��ǿ�ȣ���ֵԽ��ѹ���̶�ԽС����ȡ����ˮӡЧ��Խ�ã�
    %����ʵ�����ǿ�ȵ��ڷ�ΧΪ30��5��60ֵ������ǿ��Ϊ49��50��51�ĵط��л��䣬������48��52���м�ֵ���棬����ѡ��4.814��
    %ǿ�ȴ���60����BER��Ϊ0
%ImgWm=imread('JPEG_attack.bmp');
%}

%
%*** �Ժ�ˮӡͼ����м�����
%ImgWm=imnoise(ImgWm,'salt & pepper',0.006);  %��������'salt & pepper'������ʵ�����ǿ�ȵ��ڷ�Χ0:��0.001��0.006
%

%
%*** �Ժ�ˮӡͼ�������ת
ImgWm=imrotate(ImgWm,0.02,'bilinear','crop');  %�ڶ�������Ϊ��תǿ�ȣ����Ե���,����ʵ����ڷ�ΧΪ��0��0.01��0.1
[m,n]=size(ImgWm);
q=32;
for i=0:m/8-1
    for j=0:n/8-1
        block=ImgWm((i*8+1:(i+1)*8),(j*8+1:(j+1)*8));%��ͼƬ���ֳ�8*8��С�ķֿ�
        block_dct=dct2(block);%��ÿ���ֿ���DCT�任
        R=mod(block_dct(1,1),q);
        if R<q/2
          watermark(i*64+j+1)=0;%ˮӡΪ0
        else
          watermark(i*64+j+1)=1;%ˮӡΪ1
        end
    end
end
%��ȡԭˮӡ
message=imread('cuc.jpg');
 %���̱�ͼ��Ϊ0��1��ֵ
message=uint8(fix(double(message)./128));    
[a,b]=size(message);
watermark_reshape=reshape(watermark,[a,b]);
imshow(watermark_reshape);title('��ȡ����ˮӡͼƬ');
imwrite(watermark_reshape,'picture_after.bmp')
%��ʾ��ȡ������صı���
message_reshape=reshape(message,1,[]);
BER=sum(abs(double(message_reshape)-watermark))/(a*b),
