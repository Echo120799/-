#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define MAX_SIZE 30
void CreateStudentList(char (*number)[10],char(*name)[11],float(*score)[4],int *pStuListSize);
void InputStudentList(char(*number)[10],char(*name)[11],float(*score)[4],int numberofStudent);
void InputStudent(char (*number)[10],char (*name)[11],float (*score)[4],int location);
void EditStudent(char (*number)[10],char (*name)[11],float (*score)[4],int stuListSize,char tempnumber[]);
void DeleteStudent(char(*number)[10],char(*name)[11],float(*score)[4],int *pStuListSize);
int SearchStudent(char number[][10],int stuListSize,char tempnumber[]);
void PrintTitle();
void PrintStudent(char number[][10],char name[][11],float score[][4],int location,int order);
void SortStudent(char number[][10],char name[][11],float score[][4],int n);
void StatistStudentmath(float score[][4],int n);
void StatistStudentchinese(float score[][4],int n);
void StatistStudentenglish(float score[][4],int n);
void StatistStudentaverage(float score[][4],int n);

int main(void)
{
    int stuListSize;
	char number[MAX_SIZE][10];
	char name[MAX_SIZE][11];
	float score[MAX_SIZE][4];
	char subject[4][5]={"��ѧ","����","Ӣ��","ƽ��"};
	char choice;
	int found;
	char tempnumber[10];
	void DisplayMenu();
	int i,j;
	stuListSize=0;
	do
	{
	    DisplayMenu();
		choice=getche();
	    switch(choice)
		{
	        case'1':printf("\t\t ��ѡ���ˡ�1���������ɼ�����\n");
				    CreateStudentList(number,name,score,&stuListSize);
					break;
		    case'2':printf("\t\t ��ѡ���ˡ�2�������ѧ����\n");
				    if(stuListSize>=MAX_SIZE)
					{
						printf("ѧ���ɼ�������\n");
						system("pause");
					}
					else
					{
						fflush(stdin);
						InputStudent(number,name,score,stuListSize);
						stuListSize++;
					}
			        break;
		    case'3':printf("\t\t ��ѡ���ˡ�3�����༭ѧ����\n");
				    fflush(stdin);
				    printf("��������Ҫ�޸���Ϣ��ѧ��ѧ�ţ�\n");
	                gets(tempnumber);
				    EditStudent(number,name,score,stuListSize,tempnumber);
			        break;
		    case'4':printf("\t\t ��ѡ���ˡ�4����ɾ��ѧ����\n");
				    DeleteStudent(number,name,score,&stuListSize);
			        break;
	     	case'5':printf("\t\t ��ѡ���ˡ�5��������ѧ����\n");
				    fflush(stdin);
					printf("������Ҫ���ҵ�ѧ��ѧ�ţ�");
					gets(tempnumber);
					found=SearchStudent(number,stuListSize,tempnumber);
					if(found>-1)
					{
						PrintTitle();
						PrintStudent(number,name,score,found,1);
					}
					else
					{
						printf("����ѧ��Ϊ%s��ѧ��ʧ�ܣ�\n",tempnumber);
					}
			        break;
		    case'6':printf("\t\t ��ѡ���ˡ�6��������ɼ�����\n");
				    if(0==stuListSize)
					{
						printf("��ѧ���ɼ���¼���봴���ɼ��������ѧ����\n");
					}
					else
					{
						PrintTitle();
						for(i=0;i<stuListSize;i++)
						{
							printf("%4d%12s%12s",i+1,number[i],name[i]);
							for(j=0;j<4;j++)
								printf("%10.1f",score[i][j]);
							printf("\n");
						}
					}
			        break;
		    case'7':printf("\t\t ��ѡ���ˡ�7��������ɼ�����\n");
				    SortStudent(number,name,score,stuListSize);
			        break;
	     	case'8':printf("\t\t ��ѡ���ˡ�8����ͳ�Ƴɼ���\n");
					StatistStudentmath(score,stuListSize);
					printf("\n");
                    StatistStudentchinese(score,stuListSize);
					printf("\n");
                    StatistStudentenglish(score,stuListSize);
					printf("\n");
                    StatistStudentaverage(score,stuListSize);
			        break;
		    case'0':printf("\t\t ��ѡ���ˡ�0�����˳�ϵͳ��\n");
			        break;
		    default:printf("\t\t ������ı�Ų�����Ҫ��\n");
		}
		system("pause");

	}while(choice!='0');
	
	

}
void DisplayMenu()
{
	system("cls");
    	printf("    |-------------------------------------------------------------------|\n");
    	printf("    |                                                                   |\n");
    	printf("    |                     ������ѡ���ţ�0-8��                         |\n");
	    printf("    |                                                                   |\n");
	    printf("    |-------------------------------------------------------------------|\n");
     	printf("    |                                                                   |\n");
    	printf("    |                       1���������ɼ���                             |\n");
    	printf("    |                       2�������ѧ��                               |\n");
    	printf("    |                       3�����༭ѧ��                               |\n");
    	printf("    |                       4����ɾ��ѧ��                               |\n");
    	printf("    |                       5��������ѧ��                               |\n");
    	printf("    |                       6��������ɼ���                             |\n");
     	printf("    |                       7��������ɼ���                             |\n");
    	printf("    |                       8����ͳ�Ƴɼ�                               |\n");
    	printf("    |                       0�����˳�ϵͳ                               |\n");
    	printf("    |                                                                   |\n");
    	printf("    |                                                                   |\n");
	    printf("    |-------------------------------------------------------------------|\n");
    	printf("                               ��ѡ��\n");

}
void InputStudent(char (*number)[10],char (*name)[11],float (*score)[4],int location)
{
	printf("������ѧ�ţ�");
	gets(number[location]);
	printf("������������");
	gets(name[location]);
	printf("��������ѧ�ɼ���");
	scanf("%f",*(score+location)+0);
	if(score[location][0]>100&&score[location][0]<0)
		printf("�ɼ��Ƿ���\n");
	printf("���������ĳɼ���");
	scanf("%f",*(score+location)+1);
	if(score[location][1]>100&&score[location][1]<0)
		printf("�ɼ��Ƿ���\n");
	printf("������Ӣ��ɼ���");
	scanf("%f",*(score+location)+2);
	if(score[location][2]>100&&score[location][2]<0)
		printf("�ɼ��Ƿ���\n");
	score[location][3]=(score[location][0]+score[location][1]+score[location][2])/3;
    return;
}
void InputStudentList(char(*number)[10],char(*name)[11],float(*score)[4],int numberofStudent)
{
	int i;
	for(i=0;i<numberofStudent;i++)
	{
		fflush(stdin);
		printf("�������%2d����¼\n",i+1);
		InputStudent(number,name,score,i);
	}
	return;
}
void CreateStudentList(char (*number)[10],char(*name)[11],float(*score)[4],int *pStuListSize)
{
	int n;
	if(*pStuListSize>0)
	{
		printf("\n�������´���ѧ���ɼ���\n");
	}
	else
	{
		printf("������ѧ��������");
		scanf("%d",&n);
		if(n>0&&n<=MAX_SIZE)
		{
			InputStudentList(number,name,score,n);
			*pStuListSize=n;
			printf("����%d��ѧ����¼�ɹ���\n",*pStuListSize);
		}
		else
		{
			printf("ѧ��������ΧӦ��[1,%d]֮�䣬����ѧ���ɼ���ʧ�ܣ�\n",MAX_SIZE);
		}
	}
}
void EditStudent(char (*number)[10],char (*name)[11],float (*score)[4],int stuListSize,char tempnumber[])
{
	int found;
	int i;
	found=-1;
	for(i=0;i<stuListSize;i++)
	{
		if(0==strcmp(number[i],tempnumber))
		{
			found=i;
			break;
		}
	}
	printf("������������");
	gets(name[found]);
	printf("��������ѧ�ɼ���");
	scanf("%f",&score[found][0]);
	if(score[found][0]>100&&score[found][0]<0)
	printf("�ɼ��Ƿ���\n");
	printf("���������ĳɼ���");
	scanf("%f",&score[found][1]);
	if(score[found][1]>100&&score[found][1])
		printf("�ɼ��Ƿ���\n");
	printf("������Ӣ��ɼ���");
	scanf("%f",&score[found][2]);
	if(score[found][2]>100&&score[found][2]<0)
		printf("�ɼ��Ƿ���\n");
	score[found][3]=(score[found][0]+score[found][1]+score[found][2])/3;
	return ;
}
void DeleteStudent(char(*number)[10],char(*name)[11],float(*score)[4],int *pStuListSize)
{
	char tempnumber[10];
	int found,i;
	fflush(stdin);
	printf("������Ҫɾ��ѧ����ѧ�ţ�");
	gets(tempnumber);
	found=SearchStudent(number,*pStuListSize,tempnumber);
	if(found>-1)
	{
		for(i=found+1;i<*pStuListSize;i++)
		{
			strcpy(*(number+i-1),*(number+i));
			strcpy(*(name+i-1),*(name+i));
			*(*(score+i-1)+0)=*(*(score+i)+0);
			*(*(score+i-1)+1)=*(*(score+i)+1);
			*(*(score+i-1)+2)=*(*(score+i)+2);
			*(*(score+i-1)+3)=*(*(score+i)+3);
		}
		(*pStuListSize)--;
		printf("ɾ��ѧ��Ϊ%s��ѧ���ɹ�\n",tempnumber);
	}
	else
	{
		printf("����ѧ��Ϊ%s��ѧ��ʧ��\n",tempnumber);
	}

}
int SearchStudent(char number[][10],int stuListSize,char tempnumber[])
{
	int found;
	int i;
	found=-1;
	for(i=0;i<stuListSize;i++)
	{
		if(0==strcmp(number[i],tempnumber))
		{
			found=i;
			break;
		}
	}
	return found;
}

void PrintTitle()
{
	int i;
	printf("%4s%12s%12s%10s%10s%10s%10s\n","���","ѧ��","����","��ѧ","����","Ӣ��","ƽ��");
	for(i=1;i<=68;i++)
		putchar('=');
	printf("\n");
	return;
}
void PrintStudent(char number[][10],char name[][11],float score[][4],int location,int order)
{
	int j;
	printf("%4d%12s%12s",order,number[location],name[location]);
	for(j=0;j<4;j++)
		printf("%10.1f",score[location][j]);
		printf("\n");
	return;
}
void SortStudent(char number[][10],char name[][11],float score[][4],int n)
{
	int i,j,k;
	float temp;
	char str1[10],str2[11];
	char choice;
	printf("������ѧ�ɼ������밴0\n");
	printf("�������ĳɼ������밴1\n");
	printf("����Ӣ��ɼ������밴2\n");
	printf("����ƽ���ɼ������밴3\n");
	PrintTitle();
	choice=getche();
	switch(choice)
	{
	case'0': for(i=0;i<n-1;i++)
			{
		       for(j=0;j<n-1-i;j++)
			   {
			      if(score[j][0]<score[j+1][0])
				  {
					  strcpy(str1,number[j]);
	                  strcpy(number[j],number[j+1]);
	                  strcpy(number[j+1],str1);
	                  strcpy(str2,name[j]);
	                  strcpy(name[j],name[j+1]);
	                  strcpy(name[j+1],str2);
	                  for(k=0;k<4;k++)
					  {
	                    temp=score[j][k];
	                    score[j][k]=score[j+1][k];
	                    score[j+1][k]=temp;
					  }
				  }
			   }
             }
	          for(i=0;i<n;i++)
			  {
                 printf("%4d%12s%12s",i+1,number[i],name[i]);
	             for(j=0;j<4;j++)
	             printf("%10.1f",score[i][j]);
	             printf("\n");
			  }
				  break;
	case'1':for(i=0;i<n-1;i++)
			{
		       for(j=0;j<n-1-i;j++)
			   {
			      if(score[j][1]<score[j+1][1])
				  {
					  strcpy(str1,number[j]);
	                  strcpy(number[j],number[j+1]);
	                  strcpy(number[j+1],str1);
	                  strcpy(str2,name[j]);
	                  strcpy(name[j],name[j+1]);
	                  strcpy(name[j+1],str2);
	                  for(k=0;k<4;k++)
					  {
	                    temp=score[j][k];
	                    score[j][k]=score[j+1][k];
	                    score[j+1][k]=temp;
					  }
				 }
			 }
			}
	          for(i=0;i<n;i++)
			  {
                 printf("%4d%12s%12s",i+1,number[i],name[i]);
	             for(j=0;j<4;j++)
	             printf("%10.1f",score[i][j]);
	             printf("\n");
			  }
				  break;
	case'2':for(i=0;i<n-1;i++)
			{
		       for(j=0;j<n-1-i;j++)
			   {
			      if(score[j][2]<score[j+1][2])
				  {
					  strcpy(str1,number[j]);
	                  strcpy(number[j],number[j+1]);
	                  strcpy(number[j+1],str1);
	                  strcpy(str2,name[j]);
	                  strcpy(name[j],name[j+1]);
	                  strcpy(name[j+1],str2);
	                  for(k=0;k<4;k++)
					  {
	                    temp=score[j][k];
	                    score[j][k]=score[j+1][k];
	                    score[j+1][k]=temp;
					  }
				 }
			 }
			}
	          for(i=0;i<n;i++)
			  {
                 printf("%4d%12s%12s",i+1,number[i],name[i]);
	             for(j=0;j<4;j++)
	             printf("%10.1f",score[i][j]);
	             printf("\n");
			  }
				  break;
	case'3':for(i=0;i<n-1;i++)
			{
		       for(j=0;j<n-1-i;j++)
			   {
			      if(score[j][3]<score[j+1][3])
				  {
					  strcpy(str1,number[j]);
	                  strcpy(number[j],number[j+1]);
	                  strcpy(number[j+1],str1);
	                  strcpy(str2,name[j]);
	                  strcpy(name[j],name[j+1]);
	                  strcpy(name[j+1],str2);
	                  for(k=0;k<4;k++)
					  {
	                    temp=score[j][k];
	                    score[j][k]=score[j+1][k];
	                    score[j+1][k]=temp;
					  }
				 }
			 }
			}
	          for(i=0;i<n;i++)
			  {
                 printf("%4d%12s%12s",i+1,number[i],name[i]);
	             for(j=0;j<4;j++)
	             printf("%10.1f",score[i][j]);
	             printf("\n");
			  }
				  break;
	 default:printf("\t\t ������ı�Ų�����Ҫ��\n");

	}
	
		return;

}

void StatistStudentmath(float score[][4],int n)
{
	int i;
	int j=0,k=0,a=0,b=0,c=0;
	for(i=0;i<n;i++)
	{
		if(score[i][0]>=90&&score[i][0]<=100)
			j++;
		else if(score[i][0]>=80&&score[i][0]<90)
			k++;
		else if(score[i][0]>=70&&score[i][0]<80)
			a++;
		else if(score[i][0]>=60&&score[i][0]<70)
			b++;
		else c++;
    }
	printf("��ѧ������[90,100]֮��������ǣ�%d\n",j);
	printf("��ѧ������[80,90)֮��������ǣ�%d\n",k);
	printf("��ѧ������[70,80)֮��������ǣ�%d\n",a);
	printf("��ѧ������[60,70)֮��������ǣ�%d\n",b);
	printf("��ѧ������[0,60)֮��������ǣ�%d\n",c);
	return ;
}
void StatistStudentchinese(float score[][4],int n)
{
	int i;
	int j=0,k=0,a=0,b=0,c=0;
	for(i=0;i<n;i++)
	{
		if(score[i][1]>=90&&score[i][1]<=100)
			j++;
		else if(score[i][1]>=80&&score[i][1]<90)
			k++;
		else if(score[i][1]>=70&&score[i][1]<80)
			a++;
		else if(score[i][1]>=60&&score[i][1]<70)
			b++;
		else c++;
    }
	printf("���ķ�����[90,100]֮��������ǣ�%d\n",j);
	printf("���ķ�����[80,90)֮��������ǣ�%d\n",k);
	printf("���ķ�����[70,80)֮��������ǣ�%d\n",a);
	printf("���ķ�����[60,70)֮��������ǣ�%d\n",b);
	printf("���ķ�����[0,60)֮��������ǣ�%d\n",c);
	return ;
}
void StatistStudentenglish(float score[][4],int n)
{
	int i;
	int j=0,k=0,a=0,b=0,c=0;
	for(i=0;i<n;i++)
	{
		if(score[i][2]>=90&&score[i][2]<=100)
			j++;
		else if(score[i][2]>=80&&score[i][2]<90)
			k++;
		else if(score[i][2]>=70&&score[i][2]<80)
			a++;
		else if(score[i][2]>=60&&score[i][2]<70)
			b++;
		else c++;
    }
	printf("Ӣ�������[90,100]֮��������ǣ�%d\n",j);
	printf("Ӣ�������[80,90)֮��������ǣ�%d\n",k);
	printf("Ӣ�������[70,80)֮��������ǣ�%d\n",a);
	printf("Ӣ�������[60,70)֮��������ǣ�%d\n",b);
	printf("Ӣ�������[0,60)֮��������ǣ�%d\n",c);
	return ;
}
void StatistStudentaverage(float score[][4],int n)
{
	int i;
	int j=0,k=0,a=0,b=0,c=0;
	for(i=0;i<n;i++)
	{
		if(score[i][3]>=90&&score[i][3]<=100)
			j++;
		else if(score[i][3]>=80&&score[i][3]<90)
			k++;
		else if(score[i][3]>=70&&score[i][3]<80)
			a++;
		else if(score[i][3]>=60&&score[i][3]<70)
			b++;
		else c++;
    }
	printf("ƽ��������[90,100]֮��������ǣ�%d\n",j);
	printf("ƽ��������[80,90)֮��������ǣ�%d\n",k);
	printf("ƽ��������[70,80)֮��������ǣ�%d\n",a);
	printf("ƽ��������[60,70)֮��������ǣ�%d\n",b);
	printf("ƽ��������[0,60)֮��������ǣ�%d\n",c);
	return ;
}