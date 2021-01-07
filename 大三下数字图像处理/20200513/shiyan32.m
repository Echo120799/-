img = imread('Fig4.11(a).jpg');
subplot(221);imshow(img);title('原图');
F= double(img);
F= fftshift(fft2(img));
subplot(222);imshow(F);title('傅里叶变换');
D0 = 45;
[M,N] = size(F);
result1 = zeros(size(F));
result2 = zeros(size(F));
for i=1:M
    for j = 1:N
        D(i,j) = sqrt((i-M/2)^2+(j-N/2)^2);
        if D(i,j) <= D0
            result1(i,j)=F(i,j)*1;
        else
            result1(i,j) =0;
        end
    end
end
result1 = ifft2(ifftshift(result1));
subplot(223);imshow(real(result1),[]);title('理想低通');
Do = 52
for i=1:M
    for j = 1:N
        D(i,j) = sqrt((i-M/2)^2+(j-N/2)^2);
        if D(i,j) <= Do
            result(i,j)=F(i,j)*exp(-D(i,j)^2/(Do^2));
        else
            result(i,j) =0;
        end
    end
end
result = ifft2(ifftshift(result));
subplot(224);imshow(real(result),[]);title('高斯低通');
