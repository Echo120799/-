#include<stdio.h>
int p,q;
int main(void)
{
	int a,b;
	int hcf(int m,int n);
	int lcd(int m,int n);
	printf("����������������");
	scanf("%d%d",&a,&b);
	hcf(a,b);
	lcf(a,b);
	printf("���Լ��Ϊ��%d",p);
	printf("��С������Ϊ��%d",q);
}
int hcf(int m,int n)
{
	int a[100],x,i,j,min,max;
	if(m>n)
		min=n;
	else min=m;
	for(x=1;x<n;x++)
		if(m%x==0&&n%x==0)
		{
		    a[i]=x;
			i++;
		}
    max=a[0];
	for(j=0;j<i;j++)
		if(max<a[i])
			max=a[i];
		    p=max;
}
int lcd(int m,int n)
{
	int max,min,i=0,x;
	if(m>n)
		max=m;
	else max=n;
	for(x=max;x<=m*n;x++)
		if(x%m==0&&x%n==0)
		{
			min=x;
			break;
		}  
		 q=min;

}
