#include<iostream>
#include<pthread.h>
using namespace std;

class Lock
{
	private:
		pthread_mutex_t mtx;
	public:
		Lock()
		{
			pthread_mutex_init(&mtx,NULL);
			if(pthread_mutex_lock(&mtx) != 0)
			{
				cout<<"Error in mutex lock"<<endl;
				exit(1);
			}
		}
		~Lock()
		{
			if(pthread_mutex_unlock(&mtx) != 0)
			{
				cout<<"Error in mutex unlock"<<endl;
				exit(1);
			}
			pthread_mutex_destroy(&mtx);
		}
};
