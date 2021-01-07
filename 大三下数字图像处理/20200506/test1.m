clc;

src=imread('Fig3.10(b).jpg');
subplot(2,2,1),imshow(src);
title('原图');
src_hist=imhist(src);
subplot(2,2,2),plot(src_hist);
title('原图直方图');
J=histeq(src);
subplot(2,2,3),imshow(J);
title('均衡后图');
J_hist=imhist(J);
subplot(2,2,4),plot(J_hist);
title('均衡后直方图');