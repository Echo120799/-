function picture=pic(str)
str_ascll=abs(str);
str_bin=double(dec2bin(str_ascll))-48;
[M,N]=size(str_bin);
L=max(max(M,N),64);
picture=[L,L];
for i=1:L
    for j=1:L
        if i<=M && j<=N
            picture(i,j)=str_bin(i,j);
        else
            picture(i,j)=0;
        end
    end
end
figure;
imshow(picture);title('根据信息生成的水印图像');
