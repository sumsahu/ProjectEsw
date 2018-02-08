#include<iostream>
using namespace std;

class complex
{

	private:
		float real,imag;
	public:
		complex()
		{	

			real=imag=0;
		}
		complex(float r,float i)
		{
			real = r;
			imag = i;
		}

		complex operator +(complex c)
		{
			complex t;
			t.real = real+c.real;
			t.imag = imag+c.imag;
			return t;
		}
		complex& operator =(complex& c)
		{
			real = c.real;
			imag = c.imag;
			return *this;
		}

		void display()
		{
			cout<<"real = "<<this->real<<" imag = "<<this->imag<<endl;
		}
};

int main(int argc, char* argv[])
{
	complex c1(3.0,4.0);
	complex c2(5.0,6.0);
	complex c3 = c1+c2;
	c3.display();
	complex c4,c5;
	c4=c5=c1;
	c4.display();
	c5.display();
	return 0;
}
