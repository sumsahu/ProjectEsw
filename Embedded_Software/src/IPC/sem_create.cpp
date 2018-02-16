#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	int flags;
	mode_t perms;
	unsigned int value=1;
	flags = O_CREAT|O_EXCL|O_RDWR;
	perms = S_IRUSR|S_IWUSR;
	sem_t *sem;
	sem = sem_open("/demo",flags,perms,value);
	if(sem == SEM_FAILED)
	{
		cout<<"failed to create semaphore"<<endl;
		exit(1);
	}
	int currValue=0;
	if(sem_getvalue(sem,&currValue) == -1)
	{
		cout<<"failed to get the current value of the semaphore"<<endl;
		exit(1);
	}
	cout<<"Current value of semaphore is "<<value<<endl;
	if(sem_close(sem) == -1)
	{
		cout<<"Failed to close the sem"<<endl;
		exit(1);
	}
	if(sem_unlink("/demo") == -1)
	{
		cout<<"Failed to delete the semaphore"<<endl;
		exit(1);
	}
	return 0;

}
