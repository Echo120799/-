#include <stdio.h>
int main(void)
{
	int x,y;
	printf("������x��");
    scanf("%f,",&x);
	if(x<1)
		y=x;
	if(x>=1&&x<10)
		y=2*x-1;
	if(x>=10)
		y=3*x-11;
	return 0;
}