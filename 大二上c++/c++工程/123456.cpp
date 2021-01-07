#include <iostream.h> 
class Base 
{ 
public:
	Base(int i=1) { x = i; } 
 virtual int value() const { return x; } 
private: 
 int x; 
}; 
class Derived:public Base 
{ 
public: 
 Derived(int i=2,int j=3):Base(i){ y=j; } 
 int value()const{return Base::value()+y;} 
private: 
 int y; 
}; 
void Call(Base& a,Base b) 
{ cout<<"Value="<<a.value()<<b.value()<<endl; } 
void main() 
{ 
 Base ob1; 
 Derived ob2(40); 
 Call(ob1,ob1); 
 Call(ob2,ob2); 
} 