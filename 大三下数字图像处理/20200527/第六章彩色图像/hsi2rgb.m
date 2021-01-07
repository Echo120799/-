function rgb = hsi2rgb(HSI) 
% ��ͼ���HSI�ռ�ת����RGB�ռ� 
% �������Ϊhsiͼ���������Ϊrgb 

% �ֱ�ȡ��H��S��I���� 
H=HSI(:,:,1)*2*pi; 
S=HSI(:,:,2); 
I=HSI(:,:,3);

% ����R��G��B���������С 
R=zeros(size(H));%size(H)�����H��������������2����������һ�����������ڶ������� 
G=zeros(size(H)); 
B=zeros(size(H));

% H��[0,120�㣩���� 
sy=find((0<=H)&(H<2*pi/3)); 
B(sy)=I(sy).*(1-S(sy)); 
R(sy)=I(sy).*(1+S(sy).*cos(H(sy))./cos(pi/3-H(sy))); 
G(sy)=3*I(sy)-(R(sy)+B(sy));

% H��[120��,240�㣩���� 
sy=find((2*pi/3<=H)&(H<4*pi/3)); 
R(sy)=I(sy).*(1-S(sy)); 
G(sy)=I(sy).*(1+S(sy).*cos(H(sy)-2*pi/3)./cos(pi-H(sy))); 
B(sy)=3*I(sy)-(R(sy)+G(sy));

% H��[240��,360�㣩���� 
sy=find((4*pi/3<=H)&(H<2*pi)); 
G(sy)=I(sy).*(1-S(sy)); 
B(sy)=I(sy).*(1+S(sy).*cos(H(sy)-4*pi/3)./cos(5*pi/3-H(sy))); 
R(sy)=3*I(sy)-(G(sy)+B(sy));

%��������ȡRGBӰ�� 
rgb=cat(3,R,G,B);

end