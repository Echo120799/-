clc
clear

I=imread('plate.jpg');
subplot(2,3,1);imshow(I);title('ԭͼ');
I_gray=rgb2gray(I);
subplot(2,3,2);imshow(I_gray);title('�Ҷ�ͼ');
BW = im2bw(I_gray,0.8);
subplot(2,3,3);imshow(BW);title('��ֵͼ');
se=strel('square',2);
BW2=imopen(BW,se);
BW3 = bwareaopen(BW2,110);
subplot(2,3,4);imshow(BW3);title('��ͨ���������ĳ��ƶ�ֵͼ');
subplot(2,3,5),imshow(BW3);title('���ƶ�ֵͼ���ַ���λ���');
cc = bwconncomp(BW3);
stats = regionprops(cc, 'Area','Boundingbox');
hold on
for i=1:cc.NumObjects
       rectangle('position',stats(i).BoundingBox,'edgecolor','r');
        bb = stats(i).BoundingBox;
        %status(i).BoundingBox(1)
        %status(i).BoundingBox(2)
        xwidth=stats(i).BoundingBox(3);
        ywith=stats(i).BoundingBox(4);
        Icropletter=imcrop(BW3,bb);
end