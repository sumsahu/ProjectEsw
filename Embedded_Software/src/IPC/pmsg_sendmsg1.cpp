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
	unsigned int prio;
	ssize_t numRead;
	mode_t perms;
	mqd_t mqd;
	struct mq_attr attr;
	//flags = O_CREAT|O_EXCL|O_RDWR;
	flags = O_EXCL|O_RDWR;
	perms = S_IRUSR | S_IWUSR | S_IXUSR|S_IRGRP|S_IWGRP;
	attr.mq_maxmsg = 80;
	attr.mq_msgsize = 2048;
	mqd = mq_open("/mq",flags,perms,&attr);
	if(mqd == (mqd_t)-1)
	{
		cout<<"Failed to create the queue"<<endl;
		exit(1);
	}

	char buf[2048]="Hello Message 1 Queue\n";
	prio = 1;
	if(mq_send(mqd,buf,strlen(buf),prio) == -1)
	{
		cout<<"Failed to send the message to the queue"<<endl;
		exit(1);
	}

	strcpy(buf,"Hello Message 2 in Queue\n");
	prio = 2;
	if(mq_send(mqd,buf,strlen(buf),prio) == -1)
	{
		cout<<"Failed to send the message to the queue"<<endl;
		exit(1);
	}
	strcpy(buf,"Hello Message 3 in Queue\n");
	prio = 3;
	if(mq_send(mqd,buf,strlen(buf),prio) == -1)
	{
		cout<<"Failed to send the message to the queue"<<endl;
		exit(1);
	}
	exit(0);
}



