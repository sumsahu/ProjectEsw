#include<iostream>
using namespace std;

#define MAX 10;
class Queue
{
	private:
		int arr[MAX];
		int front,rear;
	public;
		Queue()
		{
			front = rear = -1;
		}
		void AddQueue(int value)
		{
			if(((rear == MAX-1) && front == -1) || (rear+1 == front))
			{
				cout<<"Queue is full"<<endl;
				return;
			}

		}
		int DeleteQueue()
		{
			int data;
			if(front == -1)
			{
				cout<<Queue is empty"<<endl;
				return -1;
			}
			data = arr[front];
			arr[front] = 0;
			if(front == rear)
			{
				front = rear = -1;
			}
			else
			{
				if(front == Max-1)
					front = 0;
				else
					front++;
			}	
			return data;

		}
		
};
