#include<stdio.h>
int main(void)
{
	int i,j,k,s;
	for(i=1;i<=9;i++)
	{
		for(j=9-i;j>=1;j--)
		{
			printf(" ");
		} 
		for(k=1;k<=i;k++)
		{
				printf("%d",k);
		}
		for(s=i-1;s>=1;s--)
		{
			printf("%d",s);

		}	
		
		printf("\n");
		
	}
	return 0;
}