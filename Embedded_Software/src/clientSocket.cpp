#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[])
{
	const char PORT_NUM[]="50000";
	const int BUF_SIZE=100;
	ssize_t numRead;
	int connFd;
	struct addrinfo hints;
	struct addrinfo *result,*rp;
	
	//fetch the possible list of address that can be used to bind
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_canonname=NULL;
	hints.ai_addr=NULL;
	hints.ai_next=NULL;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE|AI_NUMERICSERV;

	if(getaddrinfo(NULL,PORT_NUM,&hints,&result) == -1)
	{
		cout<<"Failed to get the address list to create and bind the socket"<<endl;
		exit(1);
	}
	for(rp=result;rp!=NULL;rp=rp->ai_next)
	{
		connFd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(connFd == -1)
		{
			cout<<"Failed to create the socket. continue with the other address"<<endl;
			continue;
		}
		if(connect(connFd,rp->ai_addr,rp->ai_addrlen) != -1)
			break;
		close(connFd);
	}
	if(rp == NULL)
	{
		cout<<"Fatal Error"<<endl;
		exit(1);
	}
	freeaddrinfo(result);
	char buf[BUF_SIZE];
	while((numRead=read(STDIN_FILENO,buf,BUF_SIZE)) > 0)
	{
		if(write(connFd,buf,numRead) != numRead)
			cout<<"Partial write"<<endl;
	}
	if((numRead=read(connFd,buf,BUF_SIZE)) > 0)
	{
		if(write(STDOUT_FILENO,buf,numRead) != numRead)
			cout<<"Partial Write"<<endl;
	}
	//close(connFd);
	return 0;
}
