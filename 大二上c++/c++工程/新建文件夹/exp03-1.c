#include<stdio.h>
int main(void)
{
	int p,q,s,r;
	char c;
    printf("请输入一组字符：");
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

    printf("字母数：%d\n空格数：%d\n数字数：%d\n其他：%d\n",p,q,s,r);
	return 0;


}

