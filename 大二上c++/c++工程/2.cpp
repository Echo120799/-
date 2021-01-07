#include<iostream.h>
int a[]={10,9,6,5,4,2,1};
void main()
{
	int n(7),i(7),x(7);
	while(x>*(a+i))
	{
		*(a+i+1)=*(a+i);
		i--;
	}
	*(a+i+1)=x;
	for(i=0;i<n;i++)
		cout<<*(a+i)<<',';
	cout<<a[i]<<endl;
}   