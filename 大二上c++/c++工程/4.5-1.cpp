#include<iostream.h>
#include<string>
void main()
{
	char str[4][20],min[20],(*p)[20];
	int i;
	p=str;//指针指向第一行字符串
	cout<<"请输入四个字符串："<<endl;
	cin>>*p>>*(p+1)>>*(p+2)>>*(p+3);
	strcpy(min,*p);//最小值初始化为第一个字符串的值
	for(i=1;i<4;i++)
		if(strcmp(*(p+i-1),*(p+i))>0)
			strcpy(min,*(p+i));//将更小的字符串的值赋给min
	cout<<"最小字符串是:"<<min<<endl;
	return;
}
