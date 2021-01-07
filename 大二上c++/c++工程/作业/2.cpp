#include<iostream.h>
int *Transform(int n,int m);
void print(int a[20]);
void main()
{
	int n,choice;
	cout<<"请输入十进制整数：";
	cin>>n;
	cout<<"请选择转化为几进制：";
	cin>>choice;
	print(Transform(n,choice));

}
int *Transform(int n,int m)
{
	static int a[20];
    int i,j;
	static int x=-1;
	for(j=0;j<20;j++)
	{
		while(n!=0)
		i=n%m;
	    a[j]=i;
		n=n/2;
		x=x+1;
	}
	return a;
}
void print(int a[20])
{
	int i;
	int b[20];
	for(i=20;i>=0;i--)
		b[20-i]=a[i];
	for(i=0;i<20;i++)
		switch(b[i])
	{
		case 10:cout<<'A';
	            break;
		case 11:cout<<'B';
	            break;
		case 12:cout<<'C';
	            break;
		case 13:cout<<'D';
	            break;
		case 14:cout<<'E';
	            break;
		case 15:cout<<'F';
	            break;
		default:cout<<b[i];
	            break;
	}
}
