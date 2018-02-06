#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
using namespace std;
/*
This is a header file for Socket
*/

class Socket
{
	private:
		int sockId;
		const char PORT_NUM[]="50000";
		const int BUF_SIZE=100;
		const int BACKLOG=50;
		struct addrinfo hint;
		struct addrinfo *result,*rp;
		
	 		
	
	public:
		Socket()
		{
			sockId=0;
		}
		

