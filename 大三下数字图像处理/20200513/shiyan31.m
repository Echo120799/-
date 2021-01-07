imgy = imread('test.bmp');
subplot(221);imshow(imgy,[]);title('Ô­Í¼ 201410513043º«Ã÷Á¼');

img = zeros(512,512);
[M,N] = size(img);
for i =1:20
    for j = 1:40
        img(i+M/2-10,j+N/2-20) = 255;
    end
end
imwrite(img,'imgtest.bmp','bmp');
I = imread('imgtest.bmp');
subplot(222);imshow(I,[]);title('´¢´æÍ¼');

 eplsion = 10e-4;
 F = double(I);
 F = fftshift(fft2(F));
 
 F2 = uint8(abs(F));
 F1 = log(1+abs(F));
 
% F_fdp = uint8(sqrt(real(F)^2+imag(F)^2));
% subplot(224),imshow(log(abs(F_fdp)+eplsion));

 subplot(223);imshow(F2,[]);title('0-255');
 subplot(224);imshow(F1,[]);title('¶ÔÊýÍ¼');


