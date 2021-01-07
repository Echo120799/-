#include <stdio.h>
int main(void)
{
	int a[11]={1,3,4,5,6,7,8,9,10,12};
	int x,i,j,temp;
	printf("请输入1个整数：\n");
	scanf("%d",&x);
	for(i=0;i<10;i++)
	{			if(x<a[i])
		{
			for(j=i;j<10;j++)
			{
			temp=x;
			x=a[j];
			a[j]=temp;
			}
		}
		else
			a[10]=x;		
	}
	for(i=0;i<11;i++)
	printf("%d  ",a[i]);
return 0;
}