clc;

src=imread('Fig3.10(b).jpg');
subplot(2,2,1),imshow(src);
title('ԭͼ');
src_hist=imhist(src);
subplot(2,2,2),plot(src_hist);
title('ԭͼֱ��ͼ');
J=histeq(src);
subplot(2,2,3),imshow(J);
title('�����ͼ');
J_hist=imhist(J);
subplot(2,2,4),plot(J_hist);
title('�����ֱ��ͼ');