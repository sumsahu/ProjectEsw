#define USE_ANON_MAP true
#ifdef USE_ANON_MAP 
#define _DEFAULT_SOURCE
#endif

#include<iostream>
#include<sys/wait.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[])
{
	int* addr;
	#ifdef USE_ANON_MAP
		addr = (int*) mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
		if(addr == MAP_FAILED)
		{
			cout<<"Failed to map the anonymous memory"<<endl;
			exit(1);
		}
	#else
		int fd;
		fd = open("/dev/zero",O_RDWR);
		if(fd == -1)
		{
			cout<<"Failed to open the file"<<endl;
			exit(1);
		}
		addr = (int*)mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if(addr == MAP_FAILED)
		{
			cout<<"Failed to map the anonymous memory"<<endl;
			exit(1);
		}
		if(close(fd) == -1)
			cout<<"Failed to close the open file descriptor"<<endl;
	#endif
	*addr = 1;

	switch(fork())
	{
		case -1:
			cout<<"Failed to create the child process"<<endl;
			exit(1);
		case 0:
			cout<<"In the child process, value = "<<*addr<<endl;
			(*addr)++;
			if(munmap(addr,sizeof(int)) == -1)
			{
				cout<<"Failed to unmap the mapped memory"<<endl;
			}
			exit(EXIT_SUCCESS);
		default:
			wait(NULL);
			cout<<"new Value is "<<*addr<<endl;
			if(munmap(addr,sizeof(int)) == -1)
			{
				cout<<"Failed to unmap the mapped memory"<<endl;
			}
			exit(EXIT_SUCCESS);			
	}

}
