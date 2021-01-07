% ************* ����DCT�任��ͼ��ˮӡ�㷨ʵ�֣�ˮӡǶ�� **************
clc
clear all;
close all;

Img=imread('lena.jpg');  %����ԭʼ����ͼ�� 

% ��ԭʼͼ��
figure(1);
imshow(Img);  %��ʾԭʼͼ��

[row column]=size(Img);             
Img_source=reshape(Img',[],1);
L=length(Img_source);               %ͼ����������
blocksize=8;                        %�ֿ�ߴ�
number_blocks=L/(blocksize^2);      %����ֿ���

% ˮӡͼ��Ԥ����
[message_pad]=copyright(number_blocks); 
  
%**** ˮӡ��Ϣ��Ƕ�� 
step=1;   %��������
s=32;     %ģֵ

for y=0:(row/blocksize-1)
    for x=0:(column/blocksize-1)
        
        %�ֿ����DCT�任
        dct_block=dct2(Img((y*blocksize+1):(y+1)*blocksize,(x*blocksize+1):(x+1)*blocksize));
        dct_block_WM=dct_block;  %���ݱ任���DCTϵ��
        
        messured_dct_block=dct_block/step;  % DCT�任����stepΪ��������
        relaxed_messured_dct_block=messured_dct_block-mod(messured_dct_block,s);  %��������ϵ����Sȡģֵ��������ȡģǰ��Ĳ�ֵ          
             
        if (message_pad(y*column/blocksize+x+1) == 0)   % ���ˮӡ����Ϊ0 ��
            dct_block_WM(1,1)=relaxed_messured_dct_block(1,1)+s/4;
            
        elseif (message_pad(y*column/blocksize+x+1) == 1)  %���ˮӡ����Ϊ1  
            dct_block_WM(1,1)=relaxed_messured_dct_block(1,1)+3*s/4;
        end
                
        % ���µ�DCTϵ��������DCT�任��ת��������
            waterMarked( y*blocksize+1:(y+1)*blocksize,x*blocksize+1:(x+1)*blocksize)=idct2(dct_block_WM); 
            
    end
end

Img_W=uint8(waterMarked);   %��������ת��
figure(2);
imshow(Img_W);          %��ʾǶ��ˮӡ���ͼ��
imwrite(Img_W,'DCTWm.bmp');  %����Ƕ��ˮӡ���ͼ��

% ����PSNR
S=PSNR(Img_W,Img),
