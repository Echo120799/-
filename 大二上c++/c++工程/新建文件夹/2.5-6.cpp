#include<iostream.h>
#include<string.h>
void main()
{
	char s[20];
	cout<<"�������ַ�����";
	cin>>s;//�����ַ���
	int i;
	i=strlen(s);//ȷ��������ַ����ĳ���
	int j;
	cout<<"����������ַ��ǣ�";
	for(j=0;j<i;j++)
		cout<<s[i-j-1];//�����һ���ַ��������
}
