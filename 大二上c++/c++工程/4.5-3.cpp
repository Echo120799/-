#include<iostream.h>
const int m=4;
const int n=4;
void main()
{
	int a[m][n],(*p)[n],i,j;
	p=a;
	cout<<"请输入"<<m<<"*"<<n<<"数组："<<endl;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			cin>>*(*(p+i)+j);
	int min=**p;//最小值初始化为第一个数
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			if(*(*(p+i)+j)<min)//将所有数与最小值依次进行比较，如果比它小就替代最小值
				min=*(*(p+i)+j);
    cout<<"最小值是："<<min<<endl;
	return ;
}