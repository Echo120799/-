#include<stdio.h>
int main(void)
{
	int a,b,c,d,temp;
	printf("ÇëÊäÈëa,b,c,dµÄÖµ£º\n");
	scanf("%d,%d,%d,%d",&a,&b,&c,&d);
	if(a>b)
	{
		temp=b;
		b=a;
		a=temp;
	}
	else if(b>c)
	{
		temp=c;
		c=b;
		b=temp;
	}
	else if(c>d)
	{
        temp=d;
		d=c;
		c=temp;
	}
	if(a>b)
	{
		temp=b;
		b=a;
		a=temp;
	}
	else if(b>c)
	{
		temp=c;
		c=b;
		b=temp;
	}
	if(a>b)
	{
		temp=b;
		b=a;
		a=temp;
	}
	printf("%d",a);
	printf("%d",b);
	printf("%d",c);
	printf("%d",d);
	return 0;
}