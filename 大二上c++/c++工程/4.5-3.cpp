#include<iostream.h>
const int m=4;
const int n=4;
void main()
{
	int a[m][n],(*p)[n],i,j;
	p=a;
	cout<<"������"<<m<<"*"<<n<<"���飺"<<endl;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			cin>>*(*(p+i)+j);
	int min=**p;//��Сֵ��ʼ��Ϊ��һ����
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			if(*(*(p+i)+j)<min)//������������Сֵ���ν��бȽϣ��������С�������Сֵ
				min=*(*(p+i)+j);
    cout<<"��Сֵ�ǣ�"<<min<<endl;
	return ;
}