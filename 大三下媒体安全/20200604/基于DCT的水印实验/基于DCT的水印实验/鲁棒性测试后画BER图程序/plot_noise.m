clc
clear all;
close all;

Noise_strenth=0:0.05:0.5;
DCT=[0 0 0 0 0.49 1.61 3.27 7.62 12.33 16.99 19.24];

figure;
plot(Noise_strenth,DCT, 'ko--', 'LineWidth', 1);
xlabel('\fontname{Times New Roman}\fontsize{12}º”‘Î«ø∂»');
ylabel('\fontname{Times New Roman}\fontsize{12}BER(%)');

