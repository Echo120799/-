%Ƕ��ˮӡ�ĺ���
%����˵��
%origne_source--ԭʼͼ������ͼ��
%watermark_source--ˮӡͼ�񣨻�ɫͼ����ֵͼ��
%��λ�������ѧ�Ű�0602��
%��ʦ��Ms.sun 
%���ߣ�����
function [U,V]=in(origne_source,watermark_source,watermarked_source)
%N=512;
%�ȴ���ˮӡͼ��(128x128)�����£�
arnold_image=Arnold(watermark_source,10,0);%����ˮӡͼ���ҽ���arnold�任��10��ʾ���еĴ�����������Կ��
%arnold_image��uint8�ĸ�ʽ
%[ca,ch,cv,cd]=dwt2(arnold_image,'haar');%����һ��dwt�任

%Ȼ��������ͼ�����£�
origne_image=imread(origne_source);%��������ͼ��
dims=ndims(origne_image);
if(dims==2)
[image_rol,image_col]=size(origne_image);
if(image_rol<512)
    if(image_col<512)
        disp('����ͼ��ĸ߶ȺͿ�ȶ��������512');
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
[LL1,LH1,HL1,HH1]=dwt2(part_origne_image2,'haar');%������ͼ���Ƚ���һ��dwt�任��320x256��
[LL2,LH2,HL2,HH2]=dwt2(LL1,'haar');%��LL1����dwt�任��160x128��
[LL3,LH3,HL3,HH3]=dwt2(LL2,'haar');%���80x64��ˮӡͼ��Ϊ64x64
%ˮӡǶ����̣����£�
%Ƕ�����������
%a1=0.15;a2=0.15;

%��������Ĵ��
arnold_image=double(arnold_image);
[UW,SW,VW]=svd(arnold_image);%��ˮӡ��svd�ֽ�
%size(SW)
[UL,SL,VL]=svd(LL3);%��3����Ƶ������svd�ֽ�80x64
SLL=SL;
%size(SL)
[UH,SH,VH]=svd(HH3);%��3����Ƶ������svd�ֽ�
SHH=SH;
%[ULH,SLH,VLH]=svd(LH3);

%[UHL,SHL,VHL]=svd(HL3);
U=UW;V=VW;%128x128
g1=0.7;g2=0.7;g3=0.5;
%���ڵ�һ������ֵ�ܴ󣬸ı�һ�㣬ͼ��ʧ��ܶ࣬����ǿ�Ȳ�Ӧ�ܴ�
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
%Ƿ����
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
LL2=idwt2(LL3,LH3,HL3,HH3,'haar');%С����任
LL1=idwt2(LL2,LH2,HL2,HH2,'haar');
watermarked_image1=idwt2(LL1,LH1,HL1,HH1,'haar');
%for i=1:N                        
%    for j=1:N
%        origne_image2(i,j)=watermarked_image1(i,j);
%    end
%end

watermarked_image=uint8(watermarked_image1);
imwrite(watermarked_image,watermarked_source);
subplot(2,2,3);imshow(origne_image);title('ԭʼͼ��');
subplot(2,2,4);imshow(watermarked_image);title('Ƕ��ˮӡ���ͼ��');
end

%%%%%%
%%%%%%
if(dims==3)
    origne_image_temp=origne_image;
    origne_image=origne_image(:,:,1);
[image_rol,image_col]=size(origne_image);
if(image_rol<512)
    if(image_col<512)
        disp('����ͼ��ĸ߶ȺͿ�ȶ��������512');
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
[LL1,LH1,HL1,HH1]=dwt2(part_origne_image2,'haar');%������ͼ���Ƚ���һ��dwt�任��320x256��
[LL2,LH2,HL2,HH2]=dwt2(LL1,'haar');%��LL1����dwt�任��160x128��
[LL3,LH3,HL3,HH3]=dwt2(LL2,'haar');%���80x64��ˮӡͼ��Ϊ64x64
%ˮӡǶ����̣����£�
%Ƕ�����������
%a1=0.15;a2=0.15;

%��������Ĵ��
arnold_image=double(arnold_image);
[UW,SW,VW]=svd(arnold_image);%��ˮӡ��svd�ֽ�
%size(SW)
[UL,SL,VL]=svd(LL3);%��3����Ƶ������svd�ֽ�80x64
SLL=SL;
%size(SL)
[UH,SH,VH]=svd(HH3);%��3����Ƶ������svd�ֽ�
SHH=SH;
%[ULH,SLH,VLH]=svd(LH3);

%[UHL,SHL,VHL]=svd(HL3);
U=UW;V=VW;%128x128
g1=0.7;g2=0.7;g3=0.5;
%���ڵ�һ������ֵ�ܴ󣬸ı�һ�㣬ͼ��ʧ��ܶ࣬����ǿ�Ȳ�Ӧ�ܴ�
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
%Ƿ����
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
LL2=idwt2(LL3,LH3,HL3,HH3,'haar');%С����任
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
subplot(2,2,3);imshow(origne_image);title('ԭʼͼ��');
subplot(2,2,4);imshow(watermarked_image);title('Ƕ��ˮӡ���ͼ��');
end

%
end