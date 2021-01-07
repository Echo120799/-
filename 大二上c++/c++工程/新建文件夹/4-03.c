#include <stdio.h>
int main()
{
   int a[15]={2,3,45,36,4,9,57,12,1,10,8,7,6,5,11};
   int i,j,k,temp,low,high,mid,key;
  for(i=0;i<14;i++)
	{
		k=i;
		for(j=i+1;j<15;j++)
		
			if(a[k]>a[j])
				k=j;
				temp=a[k];
				a[k]=a[i];
				a[i]=temp;
	}
	for(i=0;i<15;i++)
		printf("%d  ",a[i]);
		printf("\n");
  printf("输入要找的数：");
   scanf("%d",&key);
   low=0;high=14;
   while(low<=high)
   {
	   mid=(low+high)/2;
	   if(key<a[mid])
		   high=mid-1;
	   else if(key>a[mid])
		   low=mid+1;
	   else break;
   }
   if(low<=high)
	   printf("a[%d]=%d\n",mid,a[mid]);
   else
	   printf("无此数\n");
   return 0;
}


    


