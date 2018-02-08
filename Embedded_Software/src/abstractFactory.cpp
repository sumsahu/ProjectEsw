#include<iostream>
#include<list>
using namespace std;

class shape
{
	public:
	virtual void draw()=0;
};

class circle : public shape
{
	void draw()
	{
		cout<<"Circle"<<endl;
	}

};

class square : public shape
{
	void draw()
	{
		cout<<"Square"<<endl;
	}

};


class shapeFactory
{
	public:
	virtual shape* make(string s)=0;
	virtual list<std::string>& getShapeNames()=0;

};

class shapeFactoryImpl : public shapeFactory
{
	private:
		list<std::string> shapeList;
	public:
		shapeFactoryImpl()
		{}
		list<std::string>& getShapeNames()
		{
			std:string str = "circle";
			shapeList.push_back(str);
			 str = "square";
			shapeList.push_back(str);
			return shapeList;
		}
		shape* make(string s)
		{
			if ("circle" == s)
			{
				return new circle();
			}
			else if("square" == s)
			{
				return new square();
			}
		}

};

int main()
{
	shapeFactory* ptrShapeFactory;
	ptrShapeFactory = new shapeFactoryImpl();
	list<std::string> listShape = ptrShapeFactory->getShapeNames();	
	shape* ptrShape = ptrShapeFactory->make(listShape.front());
	ptrShape->draw();
	ptrShape = ptrShapeFactory->make(listShape.back());
	ptrShape->draw();
	return 0;
}
