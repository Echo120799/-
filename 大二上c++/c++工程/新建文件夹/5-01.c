#include <stdio.h>
int main(void)
{
	int p;
	int judge(int a);
	printf("������������");
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
			printf("�����������");
		else printf("����Ĳ�������");
		return 0;
		
}