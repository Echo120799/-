function str = repic(pic)
str_bin=double(pic);
[M,N]=size(str_bin);
message=zeros(1,M);
for i=1:M
    sum=0;
    for j=1:7
        sum=sum+str_bin(i,j)*(2^(7-j));
    end
    message(1,i)=(sum);
end
str=char(message);
        