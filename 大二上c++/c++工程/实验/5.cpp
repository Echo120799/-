#include<iostream.h>
void main()
{
	const int n=10;
	int a[10];
	int i,sum=0;
	a[0]=1;
	for(i=1;i<n+1;i++)
		a[i]=a[i-1]+i+1;//a[0]=1,a[1]=1+2,a[2]=1+2+3¡­¡­
	for(i=0;i<n;i++)
		sum=sum+a[i];//¼ÆËãºÍ
	cout<<sum<<endl;
}