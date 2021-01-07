#include<iostream.h>
#include<string>
const int N=10;
const int M=5;
void main()
{
	int i,j,a;
	char name[N][20];
	float score[N][M]; 
	cout<<"请输入姓名和各科成绩："<<endl;
	for(i=0;i<N;i++)
	{
		cin>>name[i];
		for(j=0;j<M;j++)
		cin>>score[i][j];
	}	
	float sum[N]={0};
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
		sum[i]=sum[i]+score[i][j];
	float max=sum[0];
	for(i=1;i<N;i++)
		if(max<sum[i])
			a=i;
		cout<<"第一名是:"<<name[a]<<endl<<"总分是："<<sum[a]<<endl;
	cout<<"请输入姓名："<<endl;
	char str2[20];
	cin>>str2;
	for(i=0;i<N;i++)
		if(strcmp(name[i],str2)==0)
			a=i;
			cout<<"各科成绩为：";
	     	for(j=0;j<M;j++)
			cout<<score[a][j]<<endl;
	return;
}