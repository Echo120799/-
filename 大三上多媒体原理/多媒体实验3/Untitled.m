clc
clear
I=imread('picture.png');
subplot(2,2,1);imshow(I);
[m,n,c]=size(I);
x=round(m/8);y=round(n/8);
Im=imcrop(I,[1,1,7,7]);
subplot(2,2,2);imshow(Im);
I1=rgb2ycbcr(Im);
I2=rgb2gray(I1);
ImDCT=dct2(I2);
Q=[16 11 10 16 24 40 51 61
    12 12 14 19 26 58 60 55
    14 13 16 24 40 57 69 56
    14 17 22 29 51 87 80 62
    18 22 37 56 68 109 103 77
    24 35 55 64 81 104 113 92
    49 64 78 87 103 121 120 101
    72 92 95 95 112 100 103 99];
for i=1:8
    for k=1:8
        ImDCT_Q(i,k)=round(ImDCT(i,k)/Q(i,k));
    end
end
for i=1:8
    for k=1:8
        ImDCT_IQ(i,k)=ImDCT_Q(i,k)*Q(i,k);
    end
end
ImR=idct2(ImDCT_IQ);
subplot(2,2,3);imshow(ImR);
for i=1:8
    for k=1:8
        Ip(i,k)=I2(i,k)-ImR(i,k);
    end
end
subplot(2,2,4);imshow(Ip);
B=8;
MAX=2^B-1;
MSE=sum(sum(Ip).^2)/(8*8);
PSNR=10*log10(MAX/sqrt(MSE))