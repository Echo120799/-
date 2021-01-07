%嵌入水印的函数
%参数说明
%origne_source--原始图像（载体图像）
%watermark_source--水印图像（灰色图像或二值图像）
%单位：江大大学信安0602班
%导师：Ms.sun 
%作者：寒星
function [U,V]=in(origne_source,watermark_source,watermarked_source)
%N=512;
%先处理水印图像(128x128)，如下：
arnold_image=Arnold(watermark_source,10,0);%读入水印图像并且进行arnold变换，10表示进行的次数（可作密钥）
%arnold_image是uint8的格式
%[ca,ch,cv,cd]=dwt2(arnold_image,'haar');%进行一级dwt变换

%然后处理载体图像，如下：
origne_image=imread(origne_source);%读入载体图像
dims=ndims(origne_image);
if(dims==2)
[image_rol,image_col]=size(origne_image);
if(image_rol<512)
    if(image_col<512)
        disp('载体图像的高度和宽度都必须大于512');
        return;
    end
end

origne_image2=double(origne_image);

%part_origne_image2=zeros(N);

%for i=1:N                        
%    for j=1:N
%        part_origne_image2(i,j)=origne_image2(i,j);
%    end
%end
part_origne_image2=origne_image2;
[LL1,LH1,HL1,HH1]=dwt2(part_origne_image2,'haar');%对载体图像先进行一级dwt变换（320x256）
[LL2,LH2,HL2,HH2]=dwt2(LL1,'haar');%对LL1进行dwt变换（160x128）
[LL3,LH3,HL3,HH3]=dwt2(LL2,'haar');%变成80x64，水印图像为64x64
%水印嵌入过程，如下：
%嵌入分两个部分
%a1=0.15;a2=0.15;

%ｃｖ，ｃｄ的存放
arnold_image=double(arnold_image);
[UW,SW,VW]=svd(arnold_image);%对水印作svd分解
%size(SW)
[UL,SL,VL]=svd(LL3);%对3级低频分量作svd分解80x64
SLL=SL;
%size(SL)
[UH,SH,VH]=svd(HH3);%对3级高频分量作svd分解
SHH=SH;
%[ULH,SLH,VLH]=svd(LH3);

%[UHL,SHL,VHL]=svd(HL3);
U=UW;V=VW;%128x128
g1=0.7;g2=0.7;g3=0.5;
%由于第一个奇异值很大，改变一点，图像失真很多，所以强度不应很大
[a,b]=size(LL3);
col=min(a,b);

SL(1,1)=SL(1,1)+g3*SW(1,1);
for i=2:col
    SL(i,i)=SL(i,i)+g1*SW(i,i);
end
SH(1,1)=SH(1,1)+g3*SW(65,65);
for i=2:col
    SH(i,i)=SH(i,i)+g2*SW(i+64,i+64);
end
%欠两下
%SLH(1,1)=SLH(1,1)+g3*SW(1,1);
%col=64;
%for i=2:col
%    SLH(i,i)=SLH(i,i)+g1*SW(i,i);
%end
%SHL(1,1)=SHL(1,1)+g3*SW(i+64,i+64);
%for i=2:col
%    SHL(i,i)=SHL(i,i)+g2*SW(i+64,i+64);
%end
LL3=UL*SL*VL';
HH3=UH*SH*VH';
%LH3=ULH*SLH*VLH';
%HL3=UHL*SHL*VHL';
LL2=idwt2(LL3,LH3,HL3,HH3,'haar');%小波逆变换
LL1=idwt2(LL2,LH2,HL2,HH2,'haar');
watermarked_image1=idwt2(LL1,LH1,HL1,HH1,'haar');
%for i=1:N                        
%    for j=1:N
%        origne_image2(i,j)=watermarked_image1(i,j);
%    end
%end

watermarked_image=uint8(watermarked_image1);
imwrite(watermarked_image,watermarked_source);
subplot(2,2,3);imshow(origne_image);title('原始图像');
subplot(2,2,4);imshow(watermarked_image);title('嵌入水印后的图像');
end

%%%%%%
%%%%%%
if(dims==3)
    origne_image_temp=origne_image;
    origne_image=origne_image(:,:,1);
[image_rol,image_col]=size(origne_image);
if(image_rol<512)
    if(image_col<512)
        disp('载体图像的高度和宽度都必须大于512');
        return;
    end
end

origne_image2=double(origne_image);

%part_origne_image2=zeros(N);

%for i=1:N                        
%    for j=1:N
%        part_origne_image2(i,j)=origne_image2(i,j);
%    end
%end
part_origne_image2=origne_image2;
[LL1,LH1,HL1,HH1]=dwt2(part_origne_image2,'haar');%对载体图像先进行一级dwt变换（320x256）
[LL2,LH2,HL2,HH2]=dwt2(LL1,'haar');%对LL1进行dwt变换（160x128）
[LL3,LH3,HL3,HH3]=dwt2(LL2,'haar');%变成80x64，水印图像为64x64
%水印嵌入过程，如下：
%嵌入分两个部分
%a1=0.15;a2=0.15;

%ｃｖ，ｃｄ的存放
arnold_image=double(arnold_image);
[UW,SW,VW]=svd(arnold_image);%对水印作svd分解
%size(SW)
[UL,SL,VL]=svd(LL3);%对3级低频分量作svd分解80x64
SLL=SL;
%size(SL)
[UH,SH,VH]=svd(HH3);%对3级高频分量作svd分解
SHH=SH;
%[ULH,SLH,VLH]=svd(LH3);

%[UHL,SHL,VHL]=svd(HL3);
U=UW;V=VW;%128x128
g1=0.7;g2=0.7;g3=0.5;
%由于第一个奇异值很大，改变一点，图像失真很多，所以强度不应很大
[a,b]=size(LL3);
col=min(a,b);

SL(1,1)=SL(1,1)+g3*SW(1,1);
for i=2:col
    SL(i,i)=SL(i,i)+g1*SW(i,i);
end
SH(1,1)=SH(1,1)+g3*SW(65,65);
for i=2:col
    SH(i,i)=SH(i,i)+g2*SW(i+64,i+64);
end
%欠两下
%SLH(1,1)=SLH(1,1)+g3*SW(1,1);
%col=64;
%for i=2:col
%    SLH(i,i)=SLH(i,i)+g1*SW(i,i);
%end
%SHL(1,1)=SHL(1,1)+g3*SW(i+64,i+64);
%for i=2:col
%    SHL(i,i)=SHL(i,i)+g2*SW(i+64,i+64);
%end
LL3=UL*SL*VL';
HH3=UH*SH*VH';
%LH3=ULH*SLH*VLH';
%HL3=UHL*SHL*VHL';
LL2=idwt2(LL3,LH3,HL3,HH3,'haar');%小波逆变换
LL1=idwt2(LL2,LH2,HL2,HH2,'haar');
watermarked_image1=idwt2(LL1,LH1,HL1,HH1,'haar');
%for i=1:N                        
%    for j=1:N
%        origne_image2(i,j)=watermarked_image1(i,j);
%    end
%end

watermarked_image=uint8(watermarked_image1);
origne_image_temp(:,:,1)=watermarked_image;
watermarked_image=origne_image_temp;
imwrite(watermarked_image,watermarked_source);
subplot(2,2,3);imshow(origne_image);title('原始图像');
subplot(2,2,4);imshow(watermarked_image);title('嵌入水印后的图像');
end

%
end