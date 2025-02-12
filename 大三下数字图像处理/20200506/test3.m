src=imread('Fig3.37(a).jpg');
gm=medfilt2(src);
subplot(1,3,1),imshow(src);
title('原图');
subplot(1,3,2),imshow(gm);
title('非线性中值滤波');
[r,c]=size(src);
w=fspecial('gaussian',[r c]);
g=imfilter(src,w);
subplot(1,3,3),imshow(g);
title('高斯平滑滤波');