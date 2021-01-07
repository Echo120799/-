#include<stdio.h>
#include<stdlib.h>
int M,N;
int main(void)
{ 
	
    int b[10][10];
	void Initialize(int a[10][10]);
	void Output(int a[10][10]);
	int Sum(int a[10][10]);
	printf("请输入行数：");
	scanf("%d",&M);
	printf("请输入列数：");
	scanf("%d",&N);
	Initialize(b);
	Output(b);
	Sum(b);
	printf("%d",Sum(b));
	return 0;
}
void Initialize(int a[10][10])
{
	int i,j;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
			a[i][j]=rand()%100;

}
void Output(int a[10][10])
{
	int i,j;
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		     printf("%10d",a[i][j]);
	    printf("\n");
	}	

}
int Sum(int a[10][10])
{
	int i,j,s=0;
	for(j=0;j<N;j++)
		s=s+a[0][j]+a[M-1][j];
	for(i=1;i<M-1;i++)
		s=s+a[i][0]+a[i][N-1];
	return s;

}
