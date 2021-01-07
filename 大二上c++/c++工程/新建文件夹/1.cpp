#include<iostream.h>
void main()
{
	char s[]="everyone";
	char *p=s;
	cout<<p+2<<',';
	cout<<*(p+2)<<',';
	while(*p)
	{
		if('e'==*p)
			*p='0';
		p++;
	}
	cout<<s<<',';
	cout<<s[2]<<',';
	cout<<s+2<<endl;
}
