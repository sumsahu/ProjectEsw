#define USE_MAP_ANON true

#ifdef USE_MAP_ANON
#define _DEFAULT_SOURCE
#endif
#include<iostream>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;

int main(int argc, char* argv[])
{
	int *addr;
	int fd;
	#ifdef USE_MAP_ANON
		cout<<"In ANONYMOUS MAPPING using MAP_ANONYMOUS"<<endl;
		addr = (int*)mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
		if(addr == MAP_FAILED)
		{
			cout<<"Failed to map anonymous mapping"<<endl;
			exit(1);
		}
	#else
		cout<<"In ANONYMOUS MAPPING using /dev/zero"<<endl;
		fd = open("/dev/zero",O_RDWR);
		if(fd == -1)
		{
			cout<<"Failed to open dev/zero"<<endl;
			exit(1);
		}
		addr = (int*)mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
		if(addr == MAP_FAILED)
		{
			cout<<"Failed to map anonymous mapping of /dev/zero"<<endl;
			exit(1);
		}
		if(close(fd) == -1)	
		{
			cout<<"Failed to close the open fd"<<endl;
		}
	#endif
	
	*addr = 1;
	switch(fork())
	{
		case -1:
			cout<<"Failed to create child process"<<endl;
			exit(1);
		case 0:
			cout<<"Child process  started, value = "<<*addr<<endl;
			(*addr)++;
			if(munmap(addr,sizeof(int)) == -1)
				cout<<"Failed to unmap the mapped memory in child"<<endl;
			exit(EXIT_SUCCESS);	
		default:
			wait(NULL);
			cout<<"Value = "<<*addr;
			if(munmap(addr,sizeof(int)) == -1)
				cout<<"Failed to unmap the mapped memory in parent"<<endl;
			exit(EXIT_SUCCESS);	
			
	}

}
