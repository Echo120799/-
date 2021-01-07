clc
clear all;
close all;

JPEG_quality_fator=50:5:95;
DCT=[33.03 29.05 21.04 16.94 3.39 0.27 0 0 0 0];

figure;
plot(JPEG_quality_fator,DCT, 'ko--', 'LineWidth', 1);
xlim([50 95]);
xlabel('\fontname{Times New Roman}\fontsize{12}JPEGÑ¹ËõÒò×Ó');
ylabel('\fontname{Times New Roman}\fontsize{12}BER(%)');

