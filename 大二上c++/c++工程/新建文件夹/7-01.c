#include<stdio.h>
int main()
{
	struct student
	{
		char number[12];
		char name[10];
		float score[4];
	};
	struct student std[10];
	int i,j=0;
	for(i=0;i<10;i++)
	{
		printf("�������%d��ѧ������Ϣ��\n",i+1);
		scanf("%s%s%f%f%f",std[i].number,std[i].name,&std[i].score[0],&std[i].score[1],&std[i].score[2]);
        std[i].score[3]=(std[i].score[0]+std[i].score[1]+std[i].score[2])/3;
		printf("��%d��ѧ����ƽ���ɼ��ǣ�%f\n",i+1,std[i].score[4]);
	}
	for(i=0;i<10;i++)
	{
		if(std[i].score[3]<60)
			j++;
	}
	printf("����������Ϊ��%d\n",j);
    return 0;
}