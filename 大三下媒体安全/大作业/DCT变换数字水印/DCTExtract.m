%************* DCT域熵掩蔽模型水印算法-提取
clc
clear ;
close all;

%读入嵌入水印后的图像
ImgWm=imread('DCTWm.bmp');  %读取未被攻击的含水印图像
[row column]=size(ImgWm);
ImgWm_source=reshape(ImgWm',[],1);
L=length(ImgWm_source);                %图像数据总数
blocksize=8;                        %分块尺寸
number_blocks=L/(blocksize^2);      %计算分块数
% 
%%{  
%*** 对含水印图像进行JPEG压缩
imwrite(ImgWm,'JPEG_attack.bmp','jpeg','Quality',55); 
    %最后的这个参数为压缩强度，其值越大压缩程度越小，提取出的水印效果越好；
    %本次实验加噪强度调节范围为30：5：60值，其中强度为49、50、51的地方有畸变，所以用48、52的中间值代替，个人选择4.814。
    %强度大于60的其BER均为0
ImgWm=imread('JPEG_attack.bmp');
%}

%{
%*** 对含水印图像进行加噪声
ImgWm=imnoise(ImgWm,'salt & pepper',0.006);  %椒盐噪声'salt & pepper'，本次实验加噪强度调节范围0:：0.001：0.006
%}

%{
%*** 对含水印图像进行旋转
ImgWm=imrotate(ImgWm,0.01,'bilinear','crop');  %第二个参数为旋转强度，可以调节,本次实验调节范围为：0：0.01：0.1
%}


%*** 水印信息的提取
step=1;  %量化步长
s=32;    %设定取模值的大小，控制嵌入强度。其大小可根据实际对不可感知性和鲁棒性的需求来调节

for y=0:(row/blocksize-1)
     for x=0:(column/blocksize-1)
        % 分块进行DCT变换
        dct_block=dct2(ImgWm((y*blocksize+1):(y+1)*blocksize,(x*blocksize+1):(x+1)*blocksize));

        % 按步长step量化，并以S为模求余数R
        R=mod(dct_block(1,1)/step,s);
        
        % 如果 s/2<=余数<s,则嵌入的水印序列为1;
        % 如果 0<=余数<s/2,则嵌入的水印序列为0;
        if ((s/2)<=R && R<s)
            message_pad_recover(y*column/blocksize+x+1)=1;
        else
            message_pad_recover(y*column/blocksize+x+1)=0;
        end
                              
     end
 end

row_picture=64;             %水印图像的垂直像素数
column_show=floor(length(message_pad_recover)/row_picture);  %嵌入的水印图像的列数

% 显示提取的水印图像
message_embed=message_pad_recover(1:column_show*row_picture);
messaage_embed_reshape=reshape(message_embed,[row_picture,column_show]);
message_show=mat2gray(messaage_embed_reshape);
figure;
imshow(message_show);title('提取的版权图像');
imwrite(message_show,'picture_after.bmp')
%载入原始水印信息
[message_pad]=copyright(number_blocks);  %原始水印图像预处理
% 显示提取错误比特的比例
%[message_pad,message_embed]=copyright(number_blocks);
len=length(message_embed);
BER=sum(abs(message_embed(1:len)-message_pad(1:len)))/len
