#include<stdio.h>
#include<math.h>
int main(void)
{
	double x,y;
	printf("��������ֵ��\n");
    scanf("%d",&x);
    if(x>1000)
	{ printf("�������������ݣ�\n");
	  if (x>1000)
		  printf("�������ݴ���");
	  return 0;
    }
	else
	{
		y=sqrt(x);
		printf("ֵΪ��",y);

	}
    return 0;
}
