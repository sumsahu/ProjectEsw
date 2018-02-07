#include<iostream>
using namespace std;

class shape
{

	public:
		virtual void getShape() =0;
};

class square : public shape
{
	public:
	 void getShape()
		{
			cout<<"Drawing square"<<endl;
		}
	
};


class circle : public shape
{
	public:
	 void getShape()
		{
			cout<<"Drawing circle"<<endl;
		}
	
};


class shapeFactory
{
	virtual shape* makeShape(string shapename)i()=0;
	virtual list<string> getShapeNames()=0;

};

class shapeFactoryImpl
{
	private:
		list<string> shapeList;
	public:
		shapeFactoryImpl()
		{
		}
		list<string>& getShapeNames()
		{
			shapeList.push_back("circle");
			shapeList.push_back("square");
			return shapeList;	
		}

};
