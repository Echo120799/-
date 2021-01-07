%************* DCT�����ڱ�ģ��ˮӡ�㷨-��ȡ
clc
clear ;
close all;

%����Ƕ��ˮӡ���ͼ��
ImgWm=imread('DCTWm.bmp');  %��ȡδ�������ĺ�ˮӡͼ��
[row column]=size(ImgWm);
ImgWm_source=reshape(ImgWm',[],1);
L=length(ImgWm_source);                %ͼ����������
blocksize=8;                        %�ֿ�ߴ�
number_blocks=L/(blocksize^2);      %����ֿ���
% 
%%{  
%*** �Ժ�ˮӡͼ�����JPEGѹ��
imwrite(ImgWm,'JPEG_attack.bmp','jpeg','Quality',55); 
    %�����������Ϊѹ��ǿ�ȣ���ֵԽ��ѹ���̶�ԽС����ȡ����ˮӡЧ��Խ�ã�
    %����ʵ�����ǿ�ȵ��ڷ�ΧΪ30��5��60ֵ������ǿ��Ϊ49��50��51�ĵط��л��䣬������48��52���м�ֵ���棬����ѡ��4.814��
    %ǿ�ȴ���60����BER��Ϊ0
ImgWm=imread('JPEG_attack.bmp');
%}

%{
%*** �Ժ�ˮӡͼ����м�����
ImgWm=imnoise(ImgWm,'salt & pepper',0.006);  %��������'salt & pepper'������ʵ�����ǿ�ȵ��ڷ�Χ0:��0.001��0.006
%}

%{
%*** �Ժ�ˮӡͼ�������ת
ImgWm=imrotate(ImgWm,0.01,'bilinear','crop');  %�ڶ�������Ϊ��תǿ�ȣ����Ե���,����ʵ����ڷ�ΧΪ��0��0.01��0.1
%}


%*** ˮӡ��Ϣ����ȡ
step=1;  %��������
s=32;    %�趨ȡģֵ�Ĵ�С������Ƕ��ǿ�ȡ����С�ɸ���ʵ�ʶԲ��ɸ�֪�Ժ�³���Ե�����������

for y=0:(row/blocksize-1)
     for x=0:(column/blocksize-1)
        % �ֿ����DCT�任
        dct_block=dct2(ImgWm((y*blocksize+1):(y+1)*blocksize,(x*blocksize+1):(x+1)*blocksize));

        % ������step����������SΪģ������R
        R=mod(dct_block(1,1)/step,s);
        
        % ��� s/2<=����<s,��Ƕ���ˮӡ����Ϊ1;
        % ��� 0<=����<s/2,��Ƕ���ˮӡ����Ϊ0;
        if ((s/2)<=R && R<s)
            message_pad_recover(y*column/blocksize+x+1)=1;
        else
            message_pad_recover(y*column/blocksize+x+1)=0;
        end
                              
     end
 end

row_picture=64;             %ˮӡͼ��Ĵ�ֱ������
column_show=floor(length(message_pad_recover)/row_picture);  %Ƕ���ˮӡͼ�������

% ��ʾ��ȡ��ˮӡͼ��
message_embed=message_pad_recover(1:column_show*row_picture);
messaage_embed_reshape=reshape(message_embed,[row_picture,column_show]);
message_show=mat2gray(messaage_embed_reshape);
figure;
imshow(message_show);title('��ȡ�İ�Ȩͼ��');
imwrite(message_show,'picture_after.bmp')
%����ԭʼˮӡ��Ϣ
[message_pad]=copyright(number_blocks);  %ԭʼˮӡͼ��Ԥ����
% ��ʾ��ȡ������صı���
%[message_pad,message_embed]=copyright(number_blocks);
len=length(message_embed);
BER=sum(abs(message_embed(1:len)-message_pad(1:len)))/len
