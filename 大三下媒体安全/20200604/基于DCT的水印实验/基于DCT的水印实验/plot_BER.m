clc
clear all;
close all;

%%{
Attack_strength=30:5:60;        %根据不同攻击修改相应的攻击强度
BER=[40.31 29.83 20.90 9.6 4.814 0.46 0];  %输入每个强度对应的BER
%}

%{
Attack_strength=0:0.001:0.006;        %根据不同攻击修改相应的攻击强度
BER=[0 4.2 8.35 13.13 15.72 18.82 23.46];  %输入每个强度对应的BER
%}

%{
Attack_strength=0:0.01:0.1;        %根据不同攻击修改相应的攻击强度
BER=[0 0.0244 1.59 3.86 6.08 8.64 10.25 11.77 12.79 13.57 14.43];  %输入每个强度对应的BER
%}

figure;
plot(Attack_strength,BER, 'bo--', 'LineWidth', 1);
xlabel('\fontname{Times New Roman}\fontsize{12}JPEG压缩强度');
%xlabel('\fontname{Times New Roman}\fontsize{12}加噪强度');
%xlabel('\fontname{Times New Roman}\fontsize{12}旋转强度');
ylabel('\fontname{Times New Roman}\fontsize{12}BER(%)');

