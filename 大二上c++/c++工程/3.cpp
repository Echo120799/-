#include<iostream.h>
void main()
{
	int a[16];
	int i;
	a[0]=1;
	a[1]=2;
	for(i=0;i<16;i++)
		a[i+2]=a[i]+a[i+1];//将1,2,3,5,8……赋值给数组a	
	double b[15];
	double sum=0;
	for(i=0;i<15;i++)
	{
		b[i]=double(a[i+1])/double(a[i]);//将分数序列赋值给数组b
	    sum=sum+b[i];//计算前15项的和
	}

		cout<<sum<<endl;

}