#include<iostream>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int main(int argc, char* argv[])
{
	char* addr;
	int fd;
	int flags;
	mode_t perms;
	flags = O_CREAT|O_RDWR;
	perms = S_IRUSR | S_IWUSR;
	//open shared memory object
	fd = shm_open(argv[1],flags,perms);
	if(fd == -1)
	{
		cout<<"Failed to create shared memory object"<<endl;
		exit(1);
	}

	//Truncate the length of the object. shm_open default creates the shared memory object of zero length
	size_t len = strlen(argv[2]);
	if(ftruncate(fd,len) == -1)
	{
		cout<<"Failed to truncate the length of the shared memory object"<<endl;
		exit(1);
	}

	//Map the shared memory object into the calling process virtual memory
	addr = (char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED)
	{
		cout<<"Failed to map the shared memory object into virtual memory"<<endl;	
		exit(1);
	}
	if(close(fd) == -1)
	{
		cout<<"Failed to close the file descriptor after use"<<endl;
	}
	//Write to the mapped memory object
	memcpy(addr,argv[2],len);
    if(munmap(addr,len) == -1)
    {
        cout<<"Failed to unmap the mapped memory"<<endl;
    }
	
	exit(EXIT_SUCCESS);
}
