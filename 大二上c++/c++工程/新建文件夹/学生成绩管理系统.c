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
	char subject[4][5]={"数学","语文","英语","平均"};
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
	        case'1':printf("\t\t 您选择了“1——创建成绩单”\n");
				    CreateStudentList(number,name,score,&stuListSize);
					break;
		    case'2':printf("\t\t 您选择了“2——添加学生”\n");
				    if(stuListSize>=MAX_SIZE)
					{
						printf("学生成绩已满！\n");
						system("pause");
					}
					else
					{
						fflush(stdin);
						InputStudent(number,name,score,stuListSize);
						stuListSize++;
					}
			        break;
		    case'3':printf("\t\t 您选择了“3——编辑学生”\n");
				    fflush(stdin);
				    printf("请输入想要修改信息的学生学号：\n");
	                gets(tempnumber);
				    EditStudent(number,name,score,stuListSize,tempnumber);
			        break;
		    case'4':printf("\t\t 您选择了“4——删除学生”\n");
				    DeleteStudent(number,name,score,&stuListSize);
			        break;
	     	case'5':printf("\t\t 您选择了“5——查找学生”\n");
				    fflush(stdin);
					printf("请输入要查找的学生学号：");
					gets(tempnumber);
					found=SearchStudent(number,stuListSize,tempnumber);
					if(found>-1)
					{
						PrintTitle();
						PrintStudent(number,name,score,found,1);
					}
					else
					{
						printf("查找学号为%s的学生失败！\n",tempnumber);
					}
			        break;
		    case'6':printf("\t\t 您选择了“6——浏览成绩单”\n");
				    if(0==stuListSize)
					{
						printf("无学生成绩记录。请创建成绩单或添加学生！\n");
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
		    case'7':printf("\t\t 您选择了“7——排序成绩单”\n");
				    SortStudent(number,name,score,stuListSize);
			        break;
	     	case'8':printf("\t\t 您选择了“8——统计成绩”\n");
					StatistStudentmath(score,stuListSize);
					printf("\n");
                    StatistStudentchinese(score,stuListSize);
					printf("\n");
                    StatistStudentenglish(score,stuListSize);
					printf("\n");
                    StatistStudentaverage(score,stuListSize);
			        break;
		    case'0':printf("\t\t 您选择了“0——退出系统”\n");
			        break;
		    default:printf("\t\t 您输入的编号不符合要求！\n");
		}
		system("pause");

	}while(choice!='0');
	
	

}
void DisplayMenu()
{
	system("cls");
    	printf("    |-------------------------------------------------------------------|\n");
    	printf("    |                                                                   |\n");
    	printf("    |                     请输入选项编号（0-8）                         |\n");
	    printf("    |                                                                   |\n");
	    printf("    |-------------------------------------------------------------------|\n");
     	printf("    |                                                                   |\n");
    	printf("    |                       1——创建成绩单                             |\n");
    	printf("    |                       2——添加学生                               |\n");
    	printf("    |                       3——编辑学生                               |\n");
    	printf("    |                       4——删除学生                               |\n");
    	printf("    |                       5——查找学生                               |\n");
    	printf("    |                       6——浏览成绩单                             |\n");
     	printf("    |                       7——排序成绩单                             |\n");
    	printf("    |                       8——统计成绩                               |\n");
    	printf("    |                       0——退出系统                               |\n");
    	printf("    |                                                                   |\n");
    	printf("    |                                                                   |\n");
	    printf("    |-------------------------------------------------------------------|\n");
    	printf("                               请选择：\n");

}
void InputStudent(char (*number)[10],char (*name)[11],float (*score)[4],int location)
{
	printf("请输入学号：");
	gets(number[location]);
	printf("请输入姓名：");
	gets(name[location]);
	printf("请输入数学成绩：");
	scanf("%f",*(score+location)+0);
	if(score[location][0]>100&&score[location][0]<0)
		printf("成绩非法！\n");
	printf("请输入语文成绩：");
	scanf("%f",*(score+location)+1);
	if(score[location][1]>100&&score[location][1]<0)
		printf("成绩非法！\n");
	printf("请输入英语成绩：");
	scanf("%f",*(score+location)+2);
	if(score[location][2]>100&&score[location][2]<0)
		printf("成绩非法！\n");
	score[location][3]=(score[location][0]+score[location][1]+score[location][2])/3;
    return;
}
void InputStudentList(char(*number)[10],char(*name)[11],float(*score)[4],int numberofStudent)
{
	int i;
	for(i=0;i<numberofStudent;i++)
	{
		fflush(stdin);
		printf("请输入第%2d条记录\n",i+1);
		InputStudent(number,name,score,i);
	}
	return;
}
void CreateStudentList(char (*number)[10],char(*name)[11],float(*score)[4],int *pStuListSize)
{
	int n;
	if(*pStuListSize>0)
	{
		printf("\n不能重新创建学生成绩单\n");
	}
	else
	{
		printf("请输入学生人数：");
		scanf("%d",&n);
		if(n>0&&n<=MAX_SIZE)
		{
			InputStudentList(number,name,score,n);
			*pStuListSize=n;
			printf("创建%d条学生记录成功！\n",*pStuListSize);
		}
		else
		{
			printf("学生人数范围应在[1,%d]之间，创建学生成绩单失败！\n",MAX_SIZE);
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
	printf("请输入姓名：");
	gets(name[found]);
	printf("请输入数学成绩：");
	scanf("%f",&score[found][0]);
	if(score[found][0]>100&&score[found][0]<0)
	printf("成绩非法！\n");
	printf("请输入语文成绩：");
	scanf("%f",&score[found][1]);
	if(score[found][1]>100&&score[found][1])
		printf("成绩非法！\n");
	printf("请输入英语成绩：");
	scanf("%f",&score[found][2]);
	if(score[found][2]>100&&score[found][2]<0)
		printf("成绩非法！\n");
	score[found][3]=(score[found][0]+score[found][1]+score[found][2])/3;
	return ;
}
void DeleteStudent(char(*number)[10],char(*name)[11],float(*score)[4],int *pStuListSize)
{
	char tempnumber[10];
	int found,i;
	fflush(stdin);
	printf("请输入要删除学生的学号：");
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
		printf("删除学号为%s的学生成功\n",tempnumber);
	}
	else
	{
		printf("查找学号为%s的学生失败\n",tempnumber);
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
	printf("%4s%12s%12s%10s%10s%10s%10s\n","序号","学号","姓名","数学","语文","英语","平均");
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
	printf("根据数学成绩排序请按0\n");
	printf("根据语文成绩排序请按1\n");
	printf("根据英语成绩排序请按2\n");
	printf("根据平均成绩排序请按3\n");
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
	 default:printf("\t\t 您输入的编号不符合要求！\n");

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
	printf("数学分数在[90,100]之间的人数是：%d\n",j);
	printf("数学分数在[80,90)之间的人数是：%d\n",k);
	printf("数学分数在[70,80)之间的人数是：%d\n",a);
	printf("数学分数在[60,70)之间的人数是：%d\n",b);
	printf("数学分数在[0,60)之间的人数是：%d\n",c);
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
	printf("语文分数在[90,100]之间的人数是：%d\n",j);
	printf("语文分数在[80,90)之间的人数是：%d\n",k);
	printf("语文分数在[70,80)之间的人数是：%d\n",a);
	printf("语文分数在[60,70)之间的人数是：%d\n",b);
	printf("语文分数在[0,60)之间的人数是：%d\n",c);
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
	printf("英语分数在[90,100]之间的人数是：%d\n",j);
	printf("英语分数在[80,90)之间的人数是：%d\n",k);
	printf("英语分数在[70,80)之间的人数是：%d\n",a);
	printf("英语分数在[60,70)之间的人数是：%d\n",b);
	printf("英语分数在[0,60)之间的人数是：%d\n",c);
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
	printf("平均分数在[90,100]之间的人数是：%d\n",j);
	printf("平均分数在[80,90)之间的人数是：%d\n",k);
	printf("平均分数在[70,80)之间的人数是：%d\n",a);
	printf("平均分数在[60,70)之间的人数是：%d\n",b);
	printf("平均分数在[0,60)之间的人数是：%d\n",c);
	return ;
}