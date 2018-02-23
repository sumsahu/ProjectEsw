#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>

using namespace std;

int main(int argc, char* argv[])
{
	char* addr;
	int fd;
	int flags;
	flags = O_RDONLY;
	fd = shm_open(argv[1],flags,0); //Opening existing shared object
	if(fd == -1)
	{
		cout<<"Failed to open the existing shared object"<<endl;
		exit(1);
	}
	struct stat sc;
	if(fstat(fd,&sc) == -1)
	{
		cout<<"Failed to get the file status"<<endl;
		exit(1);
	}
	//Map the shared memory object
	addr = (char*)mmap(NULL,sc.st_size,PROT_READ,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED)
	{
		cout<<"Failed to map the share memory object"<<endl;
		exit(1);
	}
	if(close(fd) == -1)
	{
		cout<<"Failed to close the fd"<<endl;
		exit(1);
	}
	
	//read from the shared memory object and write to the standard output
	if(write(STDOUT_FILENO,addr,sc.st_size) != sc.st_size)
		cout<<"partial write"<<endl;
	if(munmap(addr,sc.st_size) == -1)
	{
		cout<<"Failed to unmap the mapped memory"<<endl;
	}
	exit(EXIT_SUCCESS);	


}
