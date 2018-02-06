#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include "boostSerializeStl1.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	const char PORT_NUM[]="50000";
	const int BUF_SIZE=500;
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
	//char buf[BUF_SIZE];
	std::stringstream ss;
    Emp e1(61455842,"Sumit Sahu","Pune","Siemens");
    Emp e2(184317,"Garima Sahu","Pune","Credit Suisse");
    Emp e3(12345,"Sumit Garima","Pune","Dream company");
    Emp *ptr = &e3;
    Emp e4(4444444,"Champak Das","Bangalore","Nokia");
    Emp e5(5555555,"Nishant Udupi","Bangalore","Nokia");
    std::list<Emp*> empL ;
    empL.push_back(&e4);
    empL.push_back(&e5);

    Manager m1( e1, e2, ptr,empL);
	{
    boost::archive::text_oarchive oa(ss);
    oa << m1;
	}
	int size= sizeof(m1);
	cout<<"Size of object "<<size<<endl;
	char buf[size*3];
	const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    strcpy(buf,cstr);
/*
	while((numRead=read(STDIN_FILENO,buf,size*3)) > 0)
	{
		if(write(connFd,buf,numRead) != numRead)
			cout<<"Partial write"<<endl;
	}*/
	if(write(connFd,buf,strlen(buf)) != strlen(buf))
	{
			cout<<"Partial write"<<endl;
	}
	char buf1[100];
	while((numRead=read(connFd,buf1,100)) > 0)
	{
		if(write(STDOUT_FILENO,buf1,numRead) != numRead)
			cout<<"Partial Write"<<endl;
	}
	if(close(connFd) == -1)
	{
		cout<<"Failed to close the socket"<<endl;
		exit(1);
	}
	return 0;
	cout<<"About to exit"<<endl;
}
