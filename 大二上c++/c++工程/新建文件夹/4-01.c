#include <stdio.h>
int main(void)
{
	int a[10],i,j,k,temp;
	for(i=0;i<10;i++)
	{
		scanf("%d",&a[i]);
	}
     for(i=0;i<9;i++)
	{
		k=i;
		 for(j=i+1;j<10;j++)
		{
			if(a[j]<a[k])
			{
				k=j;
				temp=a[i];
				a[i]=a[k];
				a[k]=temp;
			}
			 
		}
	}
	 for(i=0;i<10;i++)
		 printf("%d",a[i]);
	 return 0;
	 

}





