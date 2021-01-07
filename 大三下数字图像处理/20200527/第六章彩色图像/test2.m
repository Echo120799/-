clc
clear

src=imread('Fig0620(a).tif');
figure(1);imshow(src);title('ԭͼ');
X=grayslice(src,32);
map = jet(32);
map(1,1)=0;
map(1,2)=0;
map(1,3)=0;
figure(2);imshow(X,map);title('α��ͼ');

























% for p=1:m
%     for q=1:n
%         if src(p,q)>0
%             x(p,q)=grayslice(src(p,q),32);
%         else
%             x(p,q)=0;
%         end
%     end
% end
