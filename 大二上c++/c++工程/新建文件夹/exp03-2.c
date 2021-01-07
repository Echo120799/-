#include<stdio.h>
int main(void)
{
	int numerator,denominator,X,i,n;
	float sum=0;
	printf("请输入正整数X和n：");
	scanf("%d%d",&X,&n);
	numerator=1;
	denominator=1;
	for(i=0;i<=n;i++)
	{
		if(i==0)
		{
			sum=1;
		}
        else 
		{
			  numerator=numerator*X;
		      denominator=denominator*i;
		      sum=sum+(float)numerator/denominator;
		}
	}
	printf("sum=%f\n",sum);
	return 0;
}