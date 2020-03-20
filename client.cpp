#include<bits/stdc++.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>

using namespace std;

#define PORT_NO 7686
#define BUF_SIZE 1024

int sfd;
void signal_callback_handler(int signum)
{
	close(sfd);
	exit(-1);
}

int main(int argc,char **argv)
{
	if(argc>=3)
	{
	    int opt;
	    signal(SIGINT, signal_callback_handler);
    	    sfd=socket(AF_INET,SOCK_STREAM,0);	
	    struct sockaddr_in client_addr;
	    client_addr.sin_family=AF_INET;
	    client_addr.sin_port=htons(PORT_NO);
	    client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	    connect(sfd,(struct sockaddr *)& client_addr,sizeof(client_addr));
	    while ((opt = getopt(argc, argv, "h:"))!= -1)
	    {
		switch(opt)
		{
  			case 'h':
			{
     				
				char buf[BUF_SIZE];
				int n;
				strcpy(buf,optarg);
				n=send(sfd,buf,sizeof(buf),0);
				if(n==-1) break;
				n=recv(sfd,buf,BUF_SIZE,0);
				if(n==-1) break;
				cout<<"DNS Packet \n";
				write(1,buf,n);
				cout<<endl; 
     				break;
			}
			default: 
			{
				cout<<"usage "<<argv[0]<<" -h website name1 -h website name2.....\n";
			}
		}	
	    }
	    close(sfd);				
	}
	else
	{	
		cout<<"usage "<<argv[0]<<" -h website name1 -h website name2.....\n";
	}		
}
