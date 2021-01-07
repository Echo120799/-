#include<stdio.h>
int main(void)
{
	int day,num;
	num=1;
	for(day=9;day>=1;day--)
	{
		num=2*(num+1);
		printf("第%d天的数量是：%d\n",day,num);
	}
	return 0;
}