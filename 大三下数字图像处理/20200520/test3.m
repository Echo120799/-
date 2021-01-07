clc
clear

src=imread('Fig0505(a)(applo17_boulder_noisy).tif');
subplot(2,2,1);imshow(src);title('原图');
src=im2double(src);
F=fftshift(fft2(src));
[m,n]=size(src);
H1=ones(m,n);
H2=ones(m,n);
H3=ones(m,n);
D0=250;
W=320;
D1=250;
W1=500;
D2=45;
for i=1:m
    for j=1:n
         d(i,j)=sqrt((i-m/2)^2+(j-n/2)^2);
         H3(i,j)=exp(-d(i,j)^2/2/D2^2);
         if (d(i,j)>(D0-W/2)&&d(i,j)<(D0+W/2))
          H1(i,j)=1-exp(-0.5*(d(i,j)^2-D0^2)/(d(i,j)^2*W)^2);
          H2(i,j)=1/(1+((d(i,j)*W1)/(d(i,j)^2-D1^2))^8);
        end
    end
end
G1=F.*H1;
A1=log(1+abs(G1));
output1=real(ifft2(ifftshift(double(G1))));
subplot(2,2,2);imshow(output1,[]);title('高斯带阻滤波器');

G2=F.*H2;
A2=log(1+abs(G2));
output2=real(ifft2(ifftshift(double(G2))));
subplot(2,2,3);imshow(output2,[]);title('巴特沃斯带阻滤波器');

G3=F.*H3;
output3=real(ifft2(ifftshift(double(G3))));
subplot(2,2,4);imshow(output3,[]);title('空域高斯平滑');
