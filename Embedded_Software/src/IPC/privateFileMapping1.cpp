#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>

using namespace std;

int main(int argc, char* argv[])
{
	char *addr;
	int fd;
	struct stat sb;
	fd = open(argv[1],O_RDONLY);
	if(fd == -1)
	{
		cout<<"Failed to open the file descriptor"<<endl;
		exit(1);
	}
	if(fstat(fd,&sb) == -1)
	{
		cout<<"Failed to get the opened file status"<<endl;
		exit(1);
	}
	addr = (char*)mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if(addr == MAP_FAILED)
	{
		cout<<"Failed to map memory "<<endl;
		exit(1);
	}
	if(write(STDOUT_FILENO,addr,sb.st_size) != sb.st_size)
		cout<<"Partial write"<<endl;
	int i = 0;
	while(i < 50)
	{
		pause();
		sleep(1);
		i++;
	}
	if(munmap(addr,sb.st_size) == -1)
	{
		cout<<"Failed to unmap the mapped memory"<<endl;
		exit(1);
	}
	
	exit(EXIT_SUCCESS);


}
