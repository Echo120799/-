function[y] = han(x,N)
x1= [1:N]';
w=0.5*(1-cos(2*pi*(x1-1)/(N-1)));
y=w.*x;
