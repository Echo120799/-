#include<stdio.h>
int main(void)
{
	int a[20],i,j;
	void swap(int a[20],int n);
	printf("��������Ҫ���е����ĸ�����");
    scanf("%d",&j);
    printf("��������Ҫ���е�����");
	for(i=0;i<j;i++)
		scanf("%d",&a[i]);
	swap(a,j);
	for(i=0;i<j;i++)
		printf("%4d",a[i]);
	return 0;
	
}
void swap(int a[20],int n)
{
	int temp,k;
	for(k=0;k<n-1;k++)
    	for(k=0;k<n-1;k++)
		  if(a[k+1]>a[k])
		  {
			  temp=a[k+1];
		      a[k+1]=a[k];
			  a[k]=temp;
		  } 
        
}