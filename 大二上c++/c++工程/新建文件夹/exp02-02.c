#include<stdio.h>
int main(void)
{
	int score;
	printf("ÇëÊäÈë³É¼¨£º");
	scanf("%d",&score);
	if(score==100&&score>=90)
		printf("A\n");
	if(score>=80&&score<90)
		printf("B\n");
	if(score>=70&&score<80)
		printf("C\n");
	if(score>=60&&score<70)
		printf("D\n");
	if(score>=0&&score<60)
		printf("E\n");
	if(score>100&&score<0)
		printf("ÊäÈë³É¼¨´íÎó£¡\n");
	return 0;
}
