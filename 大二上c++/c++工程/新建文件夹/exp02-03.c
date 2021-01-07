#include<stdio.h>
int main(void)
{
	int score,x;
	printf("ÇëÊäÈë³É¼¨£º");
	scanf("%d",&score);
	if(score>100&&score<0)
		printf("ÊäÈë³É¼¨´íÎó£¡\n");
	else x=score/10;
	switch(x)
	{
	    case 10:
	    case 9:
		     printf("A\n");
		     break;
    	case 8:
		     printf("B\n");
		     break;
    	case 7:
		     printf("C\n");
		     break;
	    case 6:
	         printf("D\n");
		     break;
	    case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		case 0:
		     printf("E\n");
	         break;
	     default:printf("ÊäÈë³É¼¨´íÎó£¡\n");
			 break;
	}

	return 0;


}