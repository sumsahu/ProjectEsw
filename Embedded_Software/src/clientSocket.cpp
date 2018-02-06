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
<<<<<<< Updated upstream
	const int BUF_SIZE = 100;
	int sockFd;
	struct addrinfo hints,*result,*rp;

=======
	const int BUF_SIZE=500;
	ssize_t numRead;
	int connFd;
	struct addrinfo hints;
	struct addrinfo *result,*rp;
	
	//fetch the possible list of address that can be used to bind
>>>>>>> Stashed changes
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

	//Call getaddrinfo to fetch the possible list of address to connect to
	if(getaddrinfo("localhost",PORT_NUM,&hints,&result) == -1)
	{
		cout<<"Failed to get the possible address list"<<endl;
		exit(1);
	}
	//Iterate through the returned list 
	for(rp = result;rp != NULL;rp = rp->ai_next)
	{
		//create socket
		sockFd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(sockFd == -1)
		{
			cout<<"Failed to create the socket"<<endl;
			continue;
		}
		if(connect(sockFd,rp->ai_addr,rp->ai_addrlen) == 0)
			break;
		close(sockFd);
	}

	if(rp == NULL)
	{
		cout<<"fatal error"<<endl;
		exit(1);
	}
<<<<<<< Updated upstream

    std::stringstream ss;
    Emp e1(61455842,"Sumit Sahu","Pune");
    Emp e2(184317,"Garima Sahu","Pune");
    Emp e3(12345,"Sumit Garima","Pune");
    Emp *ptr = &e3;
    Emp e4(4444444,"Champak Das","Bangalore");
    Emp e5(5555555,"Nishant Udupi","Bangalore");
    std::list<Emp*> empL ;
    empL.push_back(&e4);
    empL.push_back(&e5);    

    Manager m1( e1, e2, ptr,empL);
    boost::archive::text_oarchive oa(ss);
	oa << m1;
	char buf[BUF_SIZE];
	const std::string tmp = ss.str();
	const char* cstr = tmp.c_str();
	strcpy(buf,cstr);
	ssize_t numRead;
	/*while((numRead = read(STDIN_FILENO,buf,BUF_SIZE)) > 0)
	//{
		if(write(sockFd,buf,numRead) != numRead)
			cout<<"Partial write to the socket"<<endl;
	}*/
	if(write(sockFd,buf,strlen(buf)) != strlen(buf))
		cout<<"partial write"<<endl;
	cout<<"Waiting for the message from the server"<<endl;
	if((numRead = read(sockFd,buf,BUF_SIZE)) > 0)
	{
		if(write(STDOUT_FILENO,buf,numRead) != numRead)
			cout<<"Partial write to the std out"<<endl;
	}
	
	close(sockFd);
=======
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
>>>>>>> Stashed changes
	return 0;
	cout<<"About to exit"<<endl;
}
