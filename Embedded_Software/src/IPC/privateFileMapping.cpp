#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
using namespace std;
int
main(int argc, char *argv[])
{
char *addr;
int fd;
struct stat sb;
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
	cout<<"Error in opening the file"<<endl;
	exit(1);
}

if (fstat(fd, &sb) == -1)
{
	cout<<"Failed to get file status"<<endl;
	exit(1);
}
addr = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
if (addr == MAP_FAILED)
{
	cout<<"Failed to get file status"<<endl;
	exit(1);
}
if (write(STDOUT_FILENO, addr, sb.st_size) != sb.st_size)
	cout<<"partial write"<<endl;
exit(EXIT_SUCCESS);
}
