
function [message_pad,messageEmbed]=copyright(number_blocks)
% generate watermark

picture=imread('cuc.jpg');   %����ˮӡͼ��

message=picture(:,:,1);

message_embed=uint8(fix(double(message)./128));     %���̱�ͼ��Ϊ0��1��ֵ

columnRow=size(message_embed);%�̱�Ĵ�ֱˮƽ������
row=columnRow(1,1);
column=columnRow(1,2);

messageEmbed=reshape(message_embed,[1,row*column]);%���̱���ذ��տ����������н���Ƕ��
messageembed=[messageEmbed,messageEmbed];
message_pad=messageembed(1:number_blocks);
