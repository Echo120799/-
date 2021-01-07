clc
clear

I=imread('Fig0459(a)(orig_chest_xray).tif');
subplot(1,3,1);imshow(I);title('原图');
w=[1 1 1;1 -8 1;1 1 1];
g1=imfilter(I,w,'replicate');
G1=I-g1;
subplot(1,3,2);imshow(G1);title('空域拉普拉斯增强');

F=fftshift(fft2(double(I)));
[M,N]=size(I);
D0=10;
H=zeros(M,N);
for i=1:M
    for j=1:N
        if(sqrt((i-M/2)^2+(j-N/2)^2)>=D0)
            H(i,j)=exp(-((i-M/2)^2+(j-N/2)^2)/D0^2);
        end
    end
end
H1=2+5*H;
G2=F.*H1;
g2=real(ifft2(ifftshift(double(G2))));
subplot(1,3,3);imshow(g2,[]);title('频域高斯高通增强');