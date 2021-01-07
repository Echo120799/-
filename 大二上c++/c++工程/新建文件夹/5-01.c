#include <stdio.h>
int main(void)
{
	int p;
	int judge(int a);
	printf("请输入整数：");
	scanf("%d",&p);
	judge(p);

	return 0;

}

int judge(int a)
{
	int i,j=0;
	for(i=1;i<=a;i++)
		if(a%i==0)
			j++;
		if(j==2)
			printf("输入的是素数");
		else printf("输入的不是素数");
		return 0;
		
}