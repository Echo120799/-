#include<iostream.h>
void main()
{
	int a[16];
	int i;
	a[0]=1;
	a[1]=2;
	for(i=0;i<16;i++)
		a[i+2]=a[i]+a[i+1];//��1,2,3,5,8������ֵ������a	
	double b[15];
	double sum=0;
	for(i=0;i<15;i++)
	{
		b[i]=double(a[i+1])/double(a[i]);//���������и�ֵ������b
	    sum=sum+b[i];//����ǰ15��ĺ�
	}

		cout<<sum<<endl;

}