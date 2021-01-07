#include<stdio.h>
int main(void)
{
	int a[10];
	int i;
	void Sort(int m[10]);
	printf("请输入10个数：");
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);
	Sort(a);
	return 0;

}
void Sort(int *m)
{
	int i,j,k,temp;
	for(i=0;i<9;i++)
	{
        k=i;
		for(j=i+1;j<10;j++)
		{
			if(m[k]>m[j])
			{
                k=j;
				temp=m[i];
				m[i]=m[k];
				m[k]=temp;
			}
		}

	}
	printf("排序结果为：");
	for(i=0;i<10;i++)
		printf("%2d",m[i]);
		
}