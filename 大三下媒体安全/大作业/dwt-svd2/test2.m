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
%ImgWm=imrotate(ImgWm,0.05,'bilinear','crop');  %�ڶ�������Ϊ��תǿ�ȣ����Ե���,����ʵ����ڷ�ΧΪ��0��0.01��0.1

%�Ժ�ˮӡͼ�����DWT�任
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
%��ȡԭˮӡ
message=imread('cuc.jpg');
 %���̱�ͼ��Ϊ0��1��ֵ
message=uint8(fix(double(message)./128));    
[a,b]=size(message);
watermark_reshape=reshape(watermark,[a,b]);
imshow(watermark_reshape);title('��ȡ����ˮӡͼƬ');
imwrite(watermark_reshape,'water_rotate.jpg');
%��ʾ��ȡ������صı���
message_reshape=reshape(message,1,[]);
BER=sum(abs(double(message_reshape)-watermark))/(a*b),



