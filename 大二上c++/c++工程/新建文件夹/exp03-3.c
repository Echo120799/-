#include<stdio.h>
int main(void)
{
	int day,num;
	num=1;
	for(day=9;day>=1;day--)
	{
		num=2*(num+1);
		printf("��%d��������ǣ�%d\n",day,num);
	}
	return 0;
}