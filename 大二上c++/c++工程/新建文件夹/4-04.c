#include<stdio.h>
int main(void)
{
	char str1[5];
    char str2[6];
	int i=0;
	int j=0;
    printf("�������ַ���1��\n");
    scanf("%s",&str1);
    printf("�������ַ���2��\n");
    scanf("%s",&str2);
    while(str1[i]!='\0')
		i++;
    while(str2[j]!='\0')
	{
		str1[i]=str2[j];
  		i++;
		j++;
	}
	str2[j]=str1[i];
	printf("���Ϊ��%s\n",str1);
    return 0;
}