#include<stdio.h>
int main(void)
{
	int p,q,s,r;
	char c;
    printf("������һ���ַ���");
	p=0;
	q=0;
	s=0;
	r=0;
	while((c=getchar())!='\n')
	{
		if(c>='a'&&c<='z'||c>='A'&&c<='Z')
			p=p+1;
		else if(c==' ')
			  q=q+1;
		else if(c>='0'&&c<='9')
			  s=s+1;
		else r=r+1;
		
	}

    printf("��ĸ����%d\n�ո�����%d\n��������%d\n������%d\n",p,q,s,r);
	return 0;


}

