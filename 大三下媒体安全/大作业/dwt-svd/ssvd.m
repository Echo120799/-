clc
clear
m=imread('cuc.jpg');
m=double(m);
% m=[1 2 3;
%    4 5 6;
%    7 8 9
%    10 11 12];
[u s v]=svd(m)
l=u*s*v';
k=m-l;