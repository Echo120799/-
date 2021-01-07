#include<iostream.h>
#include<string.h>
static int count=0;
class Worker
{
	protected:
		unsigned int id;
		char name[11];
		float salary;
		int level;
		const float MINSALARY;
	public:
		Worker():MINSALARY(2000)
		{
			strcpy(name,"");
			level=1;
			salary=MINSALARY;
			count++;
		}
		Worker(unsigned int id,char *wname,int wlevel):MINSALARY(2000)
		{
			this->id=id;
	        strcpy(name,wname);
			level=wlevel;
	        salary=MINSALARY+200*(level-1);
         	count++;
		}
		virtual ~Worker()
		{
			count--;
		}
    	virtual float getSalary()
		{
			return salary;
		}
		virtual void infoList()
		{
			cout<<"���ţ�"<<id<<endl;
			cout<<"������"<<name<<endl;
			cout<<"�ȼ���"<<level<<endl;
		}
};
class HourWorker:public Worker
{
private:
	float hour;
	float payPerHour;
public:
	HourWorker(){}
	HourWorker(int _id,char*_name,int _level,float _hour,float _payPerHour):Worker(_id,_name,_level)
	{
		hour=_hour;
		payPerHour=_payPerHour;
	}
	~HourWorker(){};
	float getSalary()
	{
		return salary=MINSALARY+(level-1)*200+payPerHour*hour;
	}
	void infoList()
	{
		Worker::infoList();
		cout<<"ʱ����"<<hour<<endl;
		cout<<"���ʣ�"<<getSalary()<<endl;
	}
};
class PieceWorker:public Worker
{
private:
	int piece;
	float payPerPiece;
public:
	PieceWorker(){}
	PieceWorker(int _id,char*_name,int _level,int _piece,float _payPerPiece):Worker(_id,_name,_level)
	{
		piece=_piece;
		payPerPiece=_payPerPiece;
	}
	~PieceWorker(){};
	float getSalary()
	{
		return salary=MINSALARY+(level-1)*200+payPerPiece*piece;
	}
	void infoList()
	{
		Worker::infoList();
		cout<<"������"<<piece<<endl;
		cout<<"���ʣ�"<<getSalary()<<endl;
	}
};
void main()
{
	const int N=2;
	Worker *pwkArray[N];
	int i=0;
	char name[50];
	int level;
	unsigned int WorkNum;
	cout<<"����ÿСʱ���ۣ�";
	float payPerHour;
	cin>>payPerHour;
	cout<<"����ÿ�����ۣ�";
	float payPerPiece;
	cin>>payPerPiece;
	for(i=0;i<N;i++)
	{
		cout<<"�������"<<i+1<<"�����˹��ţ�";
		cin>>WorkNum;
		cout<<"�������"<<i+1<<"������������";
		cin>>name;
		cout<<"�������"<<i+1<<"�����˵ȼ���";
		cin>>level;
		cout<<"1--��ʱ  2--�Ƽ���";
		int choice;
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"����ʱ�䣺";
				float hour;
				cin>>hour;
				pwkArray[i]=new HourWorker(WorkNum,name,level,hour,payPerHour);
			break;
		case 2:
			cout<<"���������";
				int piece;
				cin>>piece;
				pwkArray[i]=new PieceWorker(WorkNum,name,level,piece,payPerPiece);
			break;
		}
	}
	for(i=0;i<N;i++)
	{
		pwkArray[i]->infoList();
	}
	float totalsalary=0.0f;
	for(i=0;i<N;i++)
	{
		totalsalary+=pwkArray[i]->getSalary();
	}
	cout<<"��������Ϊ��"<<totalsalary<<endl;
	cout<<"ƽ������Ϊ��"<<float(totalsalary/count)<<endl;
	for(i=0;i<N;i++)
	{
		if(pwkArray[i]!=NULL)
			delete pwkArray[i];
	}
}


