#include<iostream>
<<<<<<< HEAD
=======
#include<list>
>>>>>>> 9b197fe2d4d91ad6601c9bbeee05aedc0f917f75
using namespace std;

class shape
{
<<<<<<< HEAD

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
	
=======
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

>>>>>>> 9b197fe2d4d91ad6601c9bbeee05aedc0f917f75
};


class shapeFactory
{
<<<<<<< HEAD
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
=======
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
>>>>>>> 9b197fe2d4d91ad6601c9bbeee05aedc0f917f75
