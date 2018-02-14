#include<iostream>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>

using namespace std;

int main(int argc, char* argv[])
{
	int flags;
	mode_t perms;
	mqd_t mqd;
	struct mq_attr attr;
	attr.mq_maxmsg = 50;
	attr.mq_msgsize = 2048;
	flags = O_CREAT|O_RDWR;
	perms = S_IRUSR|S_IWUSR;
	mqd = mq_open("/mq",flags,perms,&attr);
	if(mqd == (mqd_t)-1)
	{
		cout<<"Failed to create the message queue"<<endl;
		exit(1);
	}

	if(mq_getattr(mqd,&attr) == -1)
	{
		cout<<"Failed to get the attributes of the message queue"<<endl;
		exit(1);
	}
	cout<<"Max messages in the queue "<<attr.mq_maxmsg<<endl;
	cout<<"Max message size "<<attr.mq_msgsize<<endl;
	cout<<"current number of messages "<<attr.mq_curmsgs<<endl;
	exit(0);
}
