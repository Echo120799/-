#include<iostream.h>
class Rectangle
{
     public:
	    void setnumber(float a,float b)
		{
			width=a;
			length=b;
		}
		float c()
		{
			return 2*(width+length);
		}
		float s()
		{
            return width*length;
		}
		void swap()
		{
			float temp;
			temp=width;
			width=length;
			length=temp;
		}
		void print()
		{
			cout<<width<<","<<length<<endl;
		}

     private:
		float width,length;

};
void main()
{
	Rectangle r1;
	r1.setnumber(4,5);
	cout<<"周长为："<<r1.c()<<endl;
	cout<<"面积为："<<r1.s()<<endl;
	cout<<"交换前长宽分别是：";
	r1.print();
	r1.swap();
	cout<<"交换前长宽分别是：";
	r1.print();

}
