function[y] = ham(x,N)
x1= [1:N]';
w=0.54-0.46*cos(2*pi*(x1-1)/(N-1));
y=w.*x;

