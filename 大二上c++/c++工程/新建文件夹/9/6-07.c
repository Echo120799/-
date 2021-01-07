#include<stdio.h>
int main(void)
{
    int i,j;
	int a[3][4];
	void sum (int *p);
	printf("请输入数值：");
	for(i=0;i<3;i++)
		for(j=0;j<4;j++)
			scanf("%d",&a[i][j]);
	printf("数组为：\n");
	for(i=0;i<3;i++)
	{
        for(j=0;j<4;j++)
			printf("%4d",a[i][j]);
		printf("\n");
	}
	sum(*a);
	return 0;
	
}
void sum (int *p)
{
	int m[3][4];
	int a,b;
	int sum=0;
	p=&m[0][0];
	for(a=0;a<3;a++)
		sum= m[a][0]+m[a][3]+sum;
	for(b=1;b<3;b++)
		sum=m[0][b]+m[2][b]+sum;
	printf("周边元素之和为：%d",sum);

}