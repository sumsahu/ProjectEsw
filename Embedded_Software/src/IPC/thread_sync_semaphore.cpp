#include<iostream>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;

sem_t *sem;

int createSemaphore()
{
	int flags;
	mode_t perms;
	unsigned int value =1;
	flags = O_RDWR | O_CREAT | O_EXCL;
	perms = S_IRUSR | S_IWUSR;
	sem = sem_open("/demo",flags,perms,value);
	if(sem == SEM_FAILED)
	{
		cout<<"Failed to create the semaphore"<<endl;
		return -1;
	}
	return 0;
}

int postToSem()
{
		

}



int main(int argc, char* argv[])
{
	

}
