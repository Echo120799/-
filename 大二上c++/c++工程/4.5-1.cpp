#include<iostream.h>
#include<string>
void main()
{
	char str[4][20],min[20],(*p)[20];
	int i;
	p=str;//ָ��ָ���һ���ַ���
	cout<<"�������ĸ��ַ�����"<<endl;
	cin>>*p>>*(p+1)>>*(p+2)>>*(p+3);
	strcpy(min,*p);//��Сֵ��ʼ��Ϊ��һ���ַ�����ֵ
	for(i=1;i<4;i++)
		if(strcmp(*(p+i-1),*(p+i))>0)
			strcpy(min,*(p+i));//����С���ַ�����ֵ����min
	cout<<"��С�ַ�����:"<<min<<endl;
	return;
}
