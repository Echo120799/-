
clc
clear 

%����Ƕ��ˮӡ���ͼ��
ImgWm=imread('picture/watermarked.bmp');  %��ȡδ�������ĺ�ˮӡͼ��

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
imwrite(watermark,'picture/water_out.jpg');


%����ȡ��ˮӡͼƬ��Ϊ�ַ���Ϣ
string = repic(watermark)
