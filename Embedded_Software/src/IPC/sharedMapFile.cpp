#include<iostream>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
#include<unistd.h>
using namespace std;

#define MEM_SIZE 20

int main(int argc, char* argv[])
{
	char* addr;
	int fd;
	fd = open(argv[1],O_RDWR);
	if(fd == -1)
	{
		cout<<"Failed to open the file"<<endl;
		exit(1);
	}
	addr =(char*) mmap(NULL,MEM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED)
	{
		cout<<"Failed to map the file to virtual memory"<<endl;
		exit(1);
	}
	if(close(fd) == -1)
		cout<<"Failed to close the file descriptor"<<endl;

	cout<<"Current string "<<addr<<endl;
	if(argc > 2)
	{
		if(strlen(argv[2]) >= MEM_SIZE)
		{
			cout<<"Error input string length is more than expected"<<endl;
			exit(1);
		}
		memset(addr,0,MEM_SIZE);
		strncpy(addr,argv[2],MEM_SIZE-1);
		cout<<"Copied "<<argv[2] << " to the file"<<endl;
		cout<<"new string "<<addr<<endl;
	}
	exit(EXIT_SUCCESS);

}
