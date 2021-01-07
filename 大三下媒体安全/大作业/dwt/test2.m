
clc
clear 


%����Ƕ��ˮӡ���ͼ��
ImgWm=imread('watermarked.jpg');  %��ȡδ�������ĺ�ˮӡͼ��

%%{  
%*** �Ժ�ˮӡͼ�����JPEGѹ��
%imwrite(ImgWm,'JPEG_attack.bmp','jpeg','Quality',55); 
%     %�����������Ϊѹ��ǿ�ȣ���ֵԽ��ѹ���̶�ԽС����ȡ����ˮӡЧ��Խ�ã�
%     %����ʵ�����ǿ�ȵ��ڷ�ΧΪ30��5��60ֵ������ǿ��Ϊ49��50��51�ĵط��л��䣬������48��52���м�ֵ���棬����ѡ��4.814��
%     %ǿ�ȴ���60����BER��Ϊ0
%ImgWm=imread('JPEG_attack.bmp');
%}

%
%*** �Ժ�ˮӡͼ����м�����
%ImgWm=imnoise(ImgWm,'salt & pepper',0.006);  %��������'salt & pepper'������ʵ�����ǿ�ȵ��ڷ�Χ0:��0.001��0.006
%imwrite(ImgWm,'noise_attack.jpg');
%

%
%*** �Ժ�ˮӡͼ�������ת
ImgWm=imrotate(ImgWm,0.05,'bilinear','crop');  %�ڶ�������Ϊ��תǿ�ȣ����Ե���,����ʵ����ڷ�ΧΪ��0��0.01��0.1
imwrite(ImgWm,'rotate_attack.jpg');
%
%����DWT�任
[cA,cH,cV,cD]=dwt2(ImgWm,'Haar');
[cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');
[cA2,cH2,cV2,cD2]=dwt2(cA1,'Haar');
[m,n]=size(cA2);
%ģֵ
q=32;
R=mod(cA2,q);
for i=1:m
    for j=1:n
    if R(i,j)>q/2
        watermark(i,j)=1;%ˮӡΪ1
    else
        watermark(i,j)=0;%ˮӡΪ0
    end
    end
end
imshow(watermark);title('��ȡ����ˮӡͼƬ');
imwrite(watermark,'water_rotate.jpg');

%����ԭʼˮӡ��Ϣ
message=imread('cuc.jpg'); 
message=uint8(fix(double(message)./128));     %���̱�ͼ��Ϊ0��1��ֵ

%��ʾ��ȡ������صı���
message_reshape=reshape(message,1,[]);
watermark_reshape=reshape(watermark,1,[]);
BER=sum(abs(double(message_reshape)-watermark_reshape))/(m*n),

