#include<iostream>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
#include<string.h>
#include<unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
	int flags;
	mode_t perms;
	mqd_t mqd;
	flags = O_CREAT|O_EXCL|O_RDWR;
	perms = S_IRUSR|S_IWUSR|S_IXUSR;
	struct mq_attr attr;
	attr.mq_maxmsg = 80;
	attr.mq_msgsize = 2048;
	mqd = mq_open("/mq",flags,perms,&attr);
	if(mqd == (mqd_t)-1)
	{
		cout<<"Failed to create the message queue"<<endl;
		exit(1);
	}
	if(mq_getattr(mqd,&attr) == -1)
	{
		cout<<"Failed to get the message queue attributes"<<endl;
		exit(1);
	}
	cout<<"Message queue max message "<<attr.mq_maxmsg<<endl;
	cout<<"Message queue max size "<<attr.mq_msgsize<<endl;

	char buf[]="Hello Message Queue\n";
	unsigned int prio = 1;
	if(mq_send(mqd,buf,strlen(buf),prio) == -1)
	{	
		cout<<"Could not send message to queue"<<endl;
		exit(1);

	}
	
	char buffer[2048];
	ssize_t numRead = mq_receive(mqd,buffer,attr.mq_msgsize,&prio);
	if(numRead == -1)
	{
		cout<<"Failed to receive the message from the queue"<<endl;
		exit(1);
	}
	cout<<"Read bytes with priority "<<(long)numRead<<" "<<prio<<endl;
	if(write(STDOUT_FILENO,buffer,numRead) != numRead)
	{
		cout<<"Partial write"<<endl;

	}
	exit(0);
	
}
