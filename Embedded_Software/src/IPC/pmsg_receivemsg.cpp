#include<iostream>
#include<unistd.h>
#include<mqueue.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
using namespace std;

int main(int argc, char* argv[])
{
	int flags;
	ssize_t numRead;
	unsigned int prio;
	mode_t perms;
	mqd_t mqd;
	flags = O_RDWR;
	mqd = mq_open("/mq",flags);
	if(mqd == (mqd_t)-1)
	{
		cout<<"Failed to open the message queue"<<endl;
		exit(1);
	}
	struct mq_attr attr;
	if(mq_getattr(mqd,&attr) == -1)
	{
	    cout<<"Failed to get the attributes of the message queue"<<endl;
	    exit(1);
	}
	cout<<"Message queue max size "<<attr.mq_msgsize<<endl;
	cout<<"Message queue max msg "<<attr.mq_maxmsg<<endl;
	for(;;)
	{
		//Receive message from the queue
		char buf[2048];
		numRead = mq_receive(mqd,buf,attr.mq_msgsize,&prio);
		if(numRead == -1)
		{
			cout<<"Failed to receive the message"<<endl;
		}
		cout<<"Received bytes "<<numRead<<" priority "<<prio<<endl;
		if(write(STDOUT_FILENO,buf,numRead) != numRead)
			cout<<"Partial write"<<endl;

	}
	exit(0);
}
