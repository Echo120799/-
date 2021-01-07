#include<stdio.h>
#include<string.h>
int main (void)
{
	char str1[10],str2[10],str3[10];
	void swap(char *x,char *y);
	printf("ÇëÊäÈëÈý¸ö×Ö·û£º");
	scanf("%s%s%s",str1,str2,str3);
	if(strcmp(str1,str2)>0)
	    swap(str1,str2);
	if(strcmp(str1,str3)>0)
		swap(str1,str3);
	if(strcmp(str2,str3)>0)
		swap(str2,str3);
	printf("%s%s%s",str1,str2,str3);
	return 0;

}
void swap(char *x,char *y)
{
	char temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
