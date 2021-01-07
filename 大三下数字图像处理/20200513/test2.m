clc
clear

I=imread('Fig4.11(a).jpg');
subplot(1,3,1);imshow(I);title('原图');
F=fftshift(fft2(double(I)));
[M,N]=size(I);

u=0:M-1;
v=0:N-1;
idx=find(u>M/2);
u(idx)=u(idx)-M;
idy=find(v>N/2);
v(idy)=v(idy)-N;
[V,U]=meshgrid(v,u); %U,V构成新的坐标系

D0=33;

H1=zeros(M,N);
for i=1:M
    for j=1:N
        if(sqrt((i-M/2)^2+(j-N/2)^2)<=D0)
            H1(i,j)=1;
        end
    end
end
G1=F.*H1;
g1=real(ifft2(ifftshift(double(G1))));
subplot(1,3,2);imshow(g1,[]);title('理想低通滤波器');

H2=zeros(M,N);
for i=1:M
    for j=1:N
        if(sqrt((i-M/2)^2+(j-N/2)^2)<=D0)
            H2(i,j)=exp(-((i-M/2)^2+(j-N/2)^2)/D0^2);
        end
    end
end
G2=F.*H2;
g2=real(ifft2(ifftshift(double(G2))));
subplot(1,3,3);imshow(g2,[]);title('高斯低通滤波器');


