#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include "boostSerializeStl1.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	const char PORT_NUM[]="50000";
	const int BACKLOG=50;
	const int BUF_SIZE=500;
	int sockFd;
	struct addrinfo hints;
	struct addrinfo *result,*rp;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

	//Call getaddrinfo to fetch the possible list of address that can be used to bind the socket
	if(getaddrinfo(NULL,PORT_NUM,&hints,&result) == -1)
	{
		cout<<"Failed to get the list of address"<<endl;
		exit(1);
	}
	
	//iterate through the returned list to check if any address can be used for binding the socket
	for(rp = result;rp != NULL;rp = rp->ai_next)
	{
		//Create socket
		sockFd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(sockFd == -1)
		{
			cout<<"Error:Failed to create the socket. Continue with the other addresses in the list."<<endl;
			continue;
		}
		if((bind(sockFd,rp->ai_addr,rp->ai_addrlen)) == 0)
			break;
		close(sockFd);
	}
	if(rp == NULL)
	{
		cout<<"Fatal Error"<<endl;
		exit(1);
	}

	freeaddrinfo(result);

	if(listen(sockFd,BACKLOG) == -1)
	{
		cout<<"Failed to listen to the socket"<<endl;
		close(sockFd);
		exit(1);
	}

	for(;;)
	{
		//Accept incoming connection
		int clientFd = accept(sockFd,NULL,NULL);
		if(clientFd == -1)
		{
			cout<<"Failed to accept the incoming connection"<<endl;
			continue;
		}
		Manager m2;
		int size = sizeof(m2);
		cout<<"Size of object "<<size<<endl;
		//char buf[BUF_SIZE];
		char buf[size*3];
	    std::stringstream ss;
    	//const std::string tmp = ss.str();
    	//const char* cstr = tmp.c_str();
    	//strcpy(buf,cstr);

		ssize_t numRead;
		if((numRead = read(clientFd,buf,size*3)) > 0)
		{
			ss << buf;
		}
		
    	boost::archive::text_iarchive ia(ss);
    	ia >> m2;
		m2.display();	
		strcpy(buf,"Hello Client\n");
		if(write(clientFd,buf,strlen(buf)) != strlen(buf))
		{
			cout<<"Partial write to client socket"<<endl;
		}
		close(clientFd);
	}

	return 0;
}
