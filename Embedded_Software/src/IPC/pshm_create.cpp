#include<iostream>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[])
{
int flags,fd;
mode_t perms;
void* addr;

flags = O_CREAT|O_RDWR;
perms = S_IRUSR | S_IWUSR;
fd = shm_open("/demo_shm",flags,perms);
if(fd == -1)
{
	cout<<"Failed to create the shared object"<<endl;
	exit(1);
}

if(ftruncate(fd,10000) == -1)
{
	cout<<"Failed to truncate the size of shared object"<<endl;
	exit(1);
}
/*Map shared memory object*/
addr = mmap(NULL,10000,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
if(addr == MAP_FAILED)
{
	cout<<"Failed to map the shared memory object"<<endl;
	exit(1);
}
exit(EXIT_SUCCESS);
}
