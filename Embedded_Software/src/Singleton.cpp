#include<iostream>
#include "Lock.h"
using namespace std;

class Singleton
{
	
	private:
		static Singleton* pInstance;
		Singleton()
		{
			i = 0;
		}
		~Singleton()
		{	
			delete pInstance;
		}
		int i;
	public:
		static Singleton* instance();
		void setData(int ii)
		{
			i = ii;
		}
		void display()
		{
			cout<<i<<endl;
		}
};

Singleton* Singleton::pInstance = NULL;

Singleton* Singleton::instance()
{
	if(pInstance == NULL)
	{
		Lock lock;
		if(pInstance == NULL)
		{
			pInstance = new Singleton();
		}
	}
	return pInstance;
}

int main()
{
	Singleton* ob1 = Singleton::instance();
	ob1->setData(10);
	ob1->display();	
	Singleton* ob2 = Singleton::instance();
	ob2->display();	
	return 0;
}
