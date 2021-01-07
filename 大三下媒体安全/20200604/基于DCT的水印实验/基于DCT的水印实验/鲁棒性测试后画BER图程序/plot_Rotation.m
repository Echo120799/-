clc
clear all;
close all;

Rotation_degree=0:0.005:0.05;
DCT=[0 1.12 4.88 8.59 11.4 14.33 16.8 18.85 20.53 22.36 23.95];

figure;
plot(Rotation_degree,DCT, 'ko--', 'LineWidth', 1);
xlim([0 0.05]);
xlabel('\fontname{Times New Roman}\fontsize{12}Ðý×ªÇ¿¶È');
ylabel('\fontname{Times New Roman}\fontsize{12}BER(%)');
