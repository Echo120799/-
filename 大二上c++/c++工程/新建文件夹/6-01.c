#include<stdio.h>
int main (void)
{
	int a,b,c;
	void swap(int *x,int *y);
	printf("请输入三个整数：");
	scanf("%d%d%d",&a,&b,&c);
	if(a>b)
	    swap(&a,&b);
	if(a>c)
		swap(&a,&c);
	if(b>c)
		swap(&b,&c);
	printf("%2d%2d%2d",a,b,c);
	return 0;

}
void swap(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}