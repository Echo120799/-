clc;
clear;

src1=imread('Fig3.40(a).jpg');
src2=imread('Fig10.10(a).jpg');
subplot(3,2,1),imshow(src1);
title('ԭͼ1');
subplot(3,2,2),imshow(src2);
title('ԭͼ2');
src1d=im2double(src1);
src2d=im2double(src2);
w=fspecial('laplacian',0);

g1 = imfilter(src1,w,'replicate');
G1=src1-g1;
subplot(3,2,3),imshow(G1);
title('ͼһ������˹��ǿ�����Խ���');imwrite(G1,'111.jpg');

g2 = imfilter(src2,w,'replicate');
G2=src2-g2;
subplot(3,2,4),imshow(G2);
title('ͼ��������˹��ǿ�����Խ���');

w2=[1 1 1;1 -8 1;1 1 1];
g3=imfilter(src1,w2,'replicate');
G3=src1-g3;
subplot(3,2,5),imshow(G3);
title('ͼһ������˹��ǿ���Խ���');imwrite(G3,'222.jpg');

g4=imfilter(src2,w2,'replicate');
G4=src2-g4;
subplot(3,2,6),imshow(G4);
title('ͼ��������˹��ǿ���Խ���');
