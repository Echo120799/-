clc
clear

I=imread('Fig0462_PET_image.tif');
%subplot(1,3,1);imshow(I);title('原图');
figure(1);imshow(I);title('原图');

F=fftshift(fft2(double(I)));
[M,N]=size(I);
rL=0.25;
rH=2;
c=1;
D0=80;

H1=zeros(M,N);
for i=1:M
    for j=1:N
        if(sqrt((i-M/2)^2+(j-N/2)^2)>=D0)
            H1(i,j)=(rH-rL)*(1-exp(-c*((i-M/2)^2+(j-N/2)^2)/D0^2)+rL);
        end
    end
end
H2=3+8*H1;
G1=F.*H2;
g1=real(ifft2(ifftshift(double(G1))));
%subplot(1,3,2);imshow(g1,[]);title('同态滤波增强');
figure(2);imshow(g1,[]);title('同态滤波增强');


H3=zeros(M,N);
for i=1:M
    for j=1:N
        if(sqrt((i-M/2)^2+(j-N/2)^2)>=D0)
            H3(i,j)=exp(-((i-M/2)^2+(j-N/2)^2)/D0^2);
        end
    end
end
H4=3+8*H3;
G2=F.*H4;
g2=real(ifft2(ifftshift(double(G2))));
%subplot(1,3,3);imshow(g2,[]);title('频域高斯高通增强');
figure(3);imshow(g2,[]);title('频域高斯高通增强');
