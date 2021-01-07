errors=(-255):255;
errorstilde=16*fix((255+errors)/8)-256+8;
signal=[20,38,56,74,92,110,128,146,164,182,200,218,236,254];%ԭʼ�ź�
signalsize=size(signal,2);%ԭʼ�źų���
errorunquantized=zeros(signalsize,1);%�������
signaltilde=errorunquantized;%�����ع��ź�
signalpredicted=errorunquantized;%Ԥ���ź�
signalpredicted(1:2)=signal(1:2);
errorquantized(1:2)=0;
signaltilde(1:2)=signal(1:2);
for i=3:signalsize
    signalpredicted(i)=fix((signaltilde(i-1)+signaltilde(i-2))/2);
    errorunquantized(i)=signal(i)-signalpredicted(i);
    errorquantized(i)=16*fix((255+errorunquantized(i))/8)-256+8;
    signaltilde(i)=signalpredicted(i)+errorquantized(i);
end
plot(signal(2:end));
xlabel('Time');
ylabel('Signal');
hold on;
plot(signaltilde(2:end),'--');
% for i=3:signalsize
%     signalpredicted(i)=fix((signaltilde(i-1)+signaltilde(i-2))/2);
%     errorunquantized(i)=signal(i)-signalpredicted(i);
%     errorquantized(i)=16*fix((255+errorunquantized(i))/16)-256+8;
% end
% plot(signal(2:end));
% xlabel('Time');
% ylabel('Signal');
% hold on;
% plot(signaltilde(2:end),'--');