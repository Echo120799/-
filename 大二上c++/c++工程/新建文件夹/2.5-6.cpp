#include<iostream.h>
#include<string.h>
void main()
{
	char s[20];
	cout<<"请输入字符串：";
	cin>>s;//输入字符串
	int i;
	i=strlen(s);//确定输入的字符串的长度
	int j;
	cout<<"倒序输出的字符是：";
	for(j=0;j<i;j++)
		cout<<s[i-j-1];//从最后一个字符倒序输出
}
