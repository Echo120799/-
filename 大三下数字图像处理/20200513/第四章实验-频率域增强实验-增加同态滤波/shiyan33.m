img=imread('Fig0459(a)(orig_chest_xray).tif');
%w4=fspecial(’laplacian’,0);
w8=[1 1 1;1 -8 1;1 1 1];
f=im2double(img);
%g4=f-imfilter(f,w4,’replicate’);
g8=2*f-imfilter(f,w8,'replicate');
subplot(231);imshow(f,[]);title('原图 201410513043');
%figure, imshow(g4)
subplot(232);imshow(g8,[]);title('空域增强');
IMG = double(img);
F = fftshift(fft2(IMG));
result = zeros(size(F));
H = zeros(size(F));
[M,N] = size(F);
Do = 12;
for i=1:M
    for j = 1:N
        D(i,j) = sqrt((i-M/2)^2+(j-N/2)^2);
        if D(i,j) <= Do
            H(i,j) = exp(-(D(i,j)^2)/(Do^2));
            %result(i,j)=F(i,j)*(1-exp(-D(i,j)^2/(Do^2)));
        else
            H(i,j) = 0;
            %result(i,j) =F(i,j);
        end
    end
end
H1 = 1-H;
result = F.*(H1);
%result = result.*(1-H);
result = ifft2(ifftshift(result));
subplot(233);imshow(real(result),[]);title('高斯高通');

H3=1+1*H1;
G3=H3.*F;
G3 = real(ifft2(ifftshift(G3)));
subplot(234);imshow(G3,[]);title('高斯强调');

G4 = (G3+78)/400;
G = histeq(G4);
subplot(235);imshow(G,[]);title('高斯强调直方图均衡化');





% 
%  f2 = im2double(f);
%  w=fspecial('laplacian',0);
%  g2=imfilter(f2,w,'replicate');
%  g = f2-g2;
%  imshow(g)


