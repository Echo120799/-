clc
clear

src=imread('homework5-1.jpg');
src=im2double(src);
f1=fspecial('average',[3,3]);
output1=imfilter(src,f1);
subplot(2,3,1);imshow(output1);title('3*3������ֵ');

output4=exp(imfilter(log(src),fspecial('average',3)));
subplot(2,3,4);imshow(output4,[]);title('3*3���ξ�ֵ�˲�');

f2=fspecial('average',[5,5]);
output2=imfilter(src,f2);
subplot(2,3,2);imshow(output2);title('5*5������ֵ');

output5=exp(imfilter(log(src),fspecial('average',5)));
subplot(2,3,5);imshow(output5,[]);title('5*5���ξ�ֵ�˲�');

f3=fspecial('average',[9,9]);
output3=imfilter(src,f3);
subplot(2,3,3);imshow(output3);title('9*9������ֵ');

output6=exp(imfilter(log(src),fspecial('average',9)));
subplot(2,3,6);imshow(output6,[]);title('9*9���ξ�ֵ�˲�');


