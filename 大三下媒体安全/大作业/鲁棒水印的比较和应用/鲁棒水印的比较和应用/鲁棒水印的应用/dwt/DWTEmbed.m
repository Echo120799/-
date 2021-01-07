 clc
 clear
 
 I=imread('picture/lena.jpg');  %����ԭʼ����ͼ�� 
 %����DWT�任
 [cA,cH,cV,cD]=dwt2(I,'Haar');
 [cA1,cH1,cV1,cD1]=dwt2(cA,'Haar');
 [cA2,cH2,cV2,cD2]=dwt2(cA1,'Haar');

 %����ˮӡͼƬ

 str=input('������������Ϣ:','s');
 message=pic(str);
 [m,n]=size(cA2);
 
 %ģֵ
 q=32;
 Z=mod(cA2,q);

 %�Ե�Ƶ�������д���
for i=1:m
    for j=1:n
        if message(i,j)==0%��Ӧλ��ˮӡֵΪ0
            if Z(i,j)>3*q/4
                cA2(i,j)=cA2(i,j)-Z(i,j)+5*q/4;
            else
                cA2(i,j)=cA2(i,j)-Z(i,j)+q/4;
            end
        else%��Ӧλ��ˮӡֵΪ1
             if Z(i,j)>q/4
                cA2(i,j)=cA2(i,j)-Z(i,j)+3*q/4;
            else
                cA2(i,j)=cA2(i,j)-Z(i,j)-q/4;
            end
        end
    end
end
%����DWT��任
k1=idwt2(cA2,cH2,cV2,cD2,'Haar');
k2=idwt2(k1,cH1,cV1,cD1,'Haar');
k3=idwt2(k2,cH,cV,cD,'Haar');
ImgWm=uint8(k3);   %��������ת��
figure;
imshow(ImgWm); title('����ˮӡ���ͼ��');
imwrite(ImgWm,'picture/watermarked.bmp'); 

%����PSNR
psnr=PSNR(ImgWm,I),
ssim=SSIM(ImgWm,I),

