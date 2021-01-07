#include<iostream.h>
class S
{
public:
	S()
	{
		PC=0;
	}
	S(S &s)
	
	{
		PC=s.PC;
		for(int i=0;i<PC;i++)
			elems[i]=s.elems[i];
	}
	void Empty()
	{
		PC=0;
	}
    int IsEmpty()
	{
		return PC==0;
	}
	int IsMemberOf(int n);
	int Add(int n);
	void Print();
private:
	int elems[100],PC;
};
int S::IsMemberOf(int n)
{
	for(int i=0;i<PC;i++)
		if(elems[i]==n)
			return 1;
		return 0;
}
int S::Add(int n)
{
	if(IsMemberOf(n))
		return 1;
	else if(PC==100)
		return 0;
	else
	{
		elems[PC++]=n;
		return 1;
	}
}
void S::Print()
{
	cout<<'{';
	for(int i=0;i<PC-1;i++)
		cout<<elems[i]<<',';
	if(PC>0)
		cout<<elems[PC-1];
	cout<<'}'<<endl;
}

void main()
{
	S a;
	cout<<a.IsEmpty()<<endl;
	a.Print();
	S b;
	for(int i=1;i<=5;i++)
		b.Add(i);
	b.Print();
	cout<<b.IsMemberOf(3)<<endl;
	cout<<b.IsEmpty()<<endl;
	for(i=6;i<=10;i++)
		b.Add(i);
	S c(b);
	c.Print();

        

}