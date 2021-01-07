clc
clear
%��ȡԭͼ
I=imread('lena.jpg');
%һ��DWT�任
[cA,cH,cV,cD]=dwt2(I,'Haar');
%ѡȡ��Ƶ����cA���к�������
[m,n]=size(cA);
%��ȡˮӡ
message=imread('cuc.jpg');
message=uint8(fix(double(message)./128));     %���̱�ͼ��Ϊ0��1��ֵ
%str=input('������������Ϣ:','s');
%message=pic(str);
%��ˮӡ����Ϊ1*��������ʽ
message_reshape=reshape(message,1,[]);
q=32;%Ƕ��ǿ��
for i=0:m/4-1
    for j=0:n/4-1
        block=cA((i*4+1:(i+1)*4),(j*4+1:(j+1)*4));%�ѵ�Ƶ����cA���ֳ�4*4��С�ķֿ�
        [U,S,V]=svd(block);%��ÿһ���ֿ��������ֵ�ֽ�
        Z=mod(S(1,1),q);%S��1,1����ÿһ���ֿ�����ֵ����ĵ�һ��Ԫ�أ����������ֵ
        k=message_reshape(i*m/4+j+1);
        if k==0%ˮӡ��Ӧ��bitλΪ0
            if Z>3*q/4
                S1=S(1,1)-Z+5*q/4;
            else
                S1=S(1,1)-Z+q/4;
            end
        else%ˮӡ��Ӧ��bitλΪ1
             if Z>q/4
                S1=S(1,1)-Z+3*q/4;
            else
                S1=S(1,1)-Z-q/4;
             end
        end
        S2=S;
        S2(1,1)=S1;
        block1=U*S2*V';%��ԭ�ֿ�
        watermark((i*4+1:(i+1)*4),(j*4+1:(j+1)*4))=block1;%�ֿ���ɴ�����ĵ�Ƶ����
    end
end
ImgWm=idwt2(watermark,cH,cV,cD,'Haar');%DWT��任
ImgWm=uint8(ImgWm);
imshow(ImgWm);title('����ˮӡ���ͼ��')
imwrite(ImgWm,'watermarked.jpg');
%����PSNR
psnr=PSNR(ImgWm,I),
ssim=SSIM(ImgWm,I),

