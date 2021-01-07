clc;
clear;
src=imread('Fig0312(a)(kidney).tif');
i=im2double(src);
s=[i>=0.5].*[i<=0.7]*0.8+[i<0.5].*i+[i>0.7].*i;
imshow(s);
