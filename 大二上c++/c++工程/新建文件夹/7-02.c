#include<stdio.h>
struct student
	{
		char number[12];
		char name[10];
		float score[4];
	};
void inputa(struct student onestudent)
{
        printf("ѧ��:\n");
		scanf("%s",onestudent.number);
		printf("������\n");
		scanf("%s",onestudent.name);
		printf("���Ƴɼ���\n");
		scanf("%f%f%f",onestudent.score[0],onestudent.score[1],onestudent.score[2]);
		
}
void input(struct student std[10])
{
	int i;
	for(i=0;i<10;i++)
	{
		printf("�������%d��ѧ������Ϣ\n",i+1);
        inputa(std[i]);
	}
}
void average(struct student std[10])
{
	int i;
	for(i=0;i<10;i++)
	{
		std[i].score[3]=(std[i].score[0]+std[i].score[1]+std[i].score[2])/3;
	}
}
int failurecount(struct student std[10])
{
   int i,j=0;
   for(i=0;i<10;i++)
   {
	   if(std[i].score[3]<60)
		   j++;
   }
   return j;
}
void output(struct student std[10])
{
    int i;
	for(i=0;i<10;i++)
	{
       printf("ѧ��:%s\n",std[i].number);
       printf("������%s\n",std[i].name);
	   printf("���Ƴɼ���%f%f%f\n",std[i].score[0],std[i].score[1],std[i].score[2]);
	}
	
}
int main()
{
	struct student std[10];
	input(std);
    average(std);
	failurecount(std);
	output(std);
	printf("�����������ǣ�\n",failurecount(std));
    return 0;

}
	
