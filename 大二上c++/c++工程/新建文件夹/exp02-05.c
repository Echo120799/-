#include<stdio.h>
#include<math.h>
int main(void)
{
	double x,y;
	printf("请输入数值：\n");
    scanf("%d",&x);
    if(x>1000)
	{ printf("请重新输入数据！\n");
	  if (x>1000)
		  printf("输入数据错误！");
	  return 0;
    }
	else
	{
		y=sqrt(x);
		printf("值为：",y);

	}
    return 0;
}
