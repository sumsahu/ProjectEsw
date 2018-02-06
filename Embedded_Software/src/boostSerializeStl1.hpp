#include<iostream>
#include<sstream>
#include<string.h>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <list>
using namespace std;

class Emp
{
	private:
		long empId;
		string name;
		string Address;
		friend class boost::serialization::access;
		template <typename Archive>
		void serialize(Archive & ar,const unsigned int version)
		{
			ar & empId;
			ar & name;
			ar & Address;
		}
	public:
		Emp(){}
		Emp(long e,string n,string add)
		{
			this->empId = e;
			this->name = n;
			this->Address = add;
		}
		void display()
		{
			cout<<"Emp Id "<<this->empId<<endl;;
			cout<<"Name "<<this->name<<endl;
			cout<<"Address "<<this->Address<<endl;
		}
};

class Manager
{
	private:
		friend class boost::serialization::access;
		Emp ceo;
		Emp MD;
		Emp *ptrEmp;
		std::list<Emp*> EmpList;
		template <typename Archive>
		void serialize(Archive & ar,const unsigned int version)
		{
			ar & ceo;
			ar & MD;
			ar & ptrEmp;
			ar & EmpList;
		}
	public:
		Manager(){}
		Manager(const Emp& empCeo,const Emp& empMD,Emp *&ptr,std::list<Emp*> &empList):ceo(empCeo),MD(empMD),ptrEmp(ptr),EmpList(empList)
		{
			//EmpList = empList;
		}
		void display()
		{
			ceo.display();
			MD.display();
			ptrEmp->display();
			cout<<"Before printing list "<<(int)EmpList.size()<<endl;
			std::list<Emp*>::iterator it =EmpList.begin();
			for(;it != EmpList.end();it++)
			{
				(*it)->display();
			}  	
		}	
		virtual ~Manager(){}
};

/*
int main(int argc, char* argv[])
{
	std::stringstream ss;
	Emp e1(61455842,"Sumit Sahu","Pune");
	Emp e2(184317,"Garima Sahu","Pune");
	Emp e3(12345,"Sumit Garima","Pune");
	Emp *ptr = &e3;
	Emp e4(4444444,"Champak Das","Bangalore");
	Emp e5(5555555,"Nishant Udupi","Bangalore");
	std::list<Emp*> empL ;
	empL.push_back(&e4);
	empL.push_back(&e5);	

	Manager m1( e1, e2, ptr,empL);
	boost::archive::text_oarchive oa(ss);
	oa << m1;
	//cout<<"Archive data "<<ss<<" "<<endl;
	boost::archive::text_iarchive ia(ss);
	Manager m2;
	ia >> m2;
	m2.display();
	return 0;
	

}*/
