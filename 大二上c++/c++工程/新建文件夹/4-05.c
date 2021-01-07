#include <stdio.h>
int main(void)
{
	int m,n,i,j,k,max;
	int a[m][n];
	printf("请输入：\n");
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
    for(i=0;i<m;i++)
		max=a[m][0];
	for(j=0;j<n;j++)
	{
		if(a[i][j]>max)
			max=a[i][j];
            n=j;
	}
	for(i=0;i<m;i++)
		if(max<a[i][n])
			printf("是鞍点");
		else printf("无鞍点");
   return 0;
}

	




    
