% clc;clear;
function [message_pad,messageEmbed]=copyright(number_blocks)
% generate watermark
% number_blocks=12288;
% picture=imread('cuc.jpg');   %读入水印图像
% message=picture(:,:,1);
% message_embed=uint8(fix(double(message)./128));     %将商标图变为0、1二值

str=input('请输入隐藏信息:','s');
message_embed=pic(str);
columnRow=size(message_embed);%商标的垂直水平像素数
row=columnRow(1,1);
column=columnRow(1,2);

messageEmbed=reshape(message_embed,[1,row*column]);%将商标比特按照块数多少排列进行嵌入
messageembed=[messageEmbed,messageEmbed,messageEmbed];
message_pad=messageembed(1:number_blocks);
