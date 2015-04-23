#include "udp.h"      

std::vector< std::pair<long long,long long> > IPdata;
std::vector<long long>TimeStamp;
std::queue<std::string> Instructions;


bool First=true;
bool Connect;
bool playersReady;
bool isOffline;
bool noIP;

std::string ipadr;

int sid;
int LastTime;

struct IPMessage {
    long long ip;
    char* message;
    int sockid;
};

std::string GetIP()
{
	return ipadr;
}
bool IsBaap()
{
	if(IPdata.size()>0)
	{
		if(IPdata[0].second==1)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

std::string ToStr(char* arr)  
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i];
    }
    return ans;
}

int GetNumPlayers()
{
	return IPdata.size();
}

void AddPlayers(char players [])
{
	std::string s;
    // std::cout<<"Adding player:"<<ToStr(players);
	for(int i=2;players[i]!=0;i++)
	{
		if(players[i]!=' ' && players[i]!='\n')
			s=s+players[i];
		else
		{	
			std::pair<long long,long long> p;
			if(s[s.size()-1]=='*')
			{	
				p.second=1;
				s=s.substr(0,s.size()-1);
			}
			else
				p.second=0;

			const char * ipchar = s.c_str();
			p.first=atoll(ipchar);
            // std::cout<<"first element of p:"<<p.first<<std::endl;
            // std::cout<<"second element of p:"<<p.second<<std::endl;
			TimeStamp.push_back(time(0));
			IPdata.push_back(p);
            // for(int i=0;i<IPdata.size();i++)
                // std::cout<<IPdata[i].first<<std::endl;
			s="";
		}
	}
}

int LengthNum(long long num)
{
	int ans=0;
	while(num>0)
	{
		num=num/10;
		ans++;
	}
	return ans;
}

int FindIndex(long long ip)
{
	for(int i=0;i<IPdata.size();i++)
	{
		if(IPdata[i].first==ip)
			return i;
	}
	return -1;
}

void *SendMessage(void* id)
{
    IPMessage  *pa= (IPMessage *)id;
    long long ip=pa->ip;
    char * message=pa->message;
    int sockid=pa->sockid;
    struct sockaddr_in remaddr;
    int slen=sizeof(remaddr);

    memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_addr.s_addr=ip;
	remaddr.sin_port = htons(SERVICE_PORT);
    // std::cout<<"sending:"<<ToStr(message)<<std::endl;
    if(FindIndex((long long)remaddr.sin_addr.s_addr)>0)
    {	
		int bytes_sent=sendto(sockid, message, strlen(message), 0, (struct sockaddr *)&remaddr, slen);
		// std::cout<<"bytes sent: "<<bytes_sent<<std::endl;
		// if(bytes_sent<=0)
		// {
		// 	bytes_sent=sendto(sockid, message, strlen(message), 0, (struct sockaddr *)&remaddr, slen);
		// 	if(bytes_sent<=0)
		// 	{
		// 		std::cout<<"Player disconnected:"<<ip<<std::endl;
		// 		if(FindIndex(ip)>0)
		// 		{	
		// 			IPdata.erase(IPdata.begin()+FindIndex(ip));
		// 			TimeStamp.erase(TimeStamp.begin()+FindIndex(ip));
		// 		}
		// 	}
		// }
	} 
	pthread_exit(NULL);
}

char* ToArr(std::string str)  
{
    // char* ans=new char[str.size()]; //answer of this function
    // for(int i=0;i<str.size();i++)
    // {
    //     ans[i]=str[i];
    // }
    // ans[str.size()]='\0';
    // return ans;
    // delete [] ans;
    char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
	delete [] cstr;

}

void SendMessageToAll(std::string message)
{
	if(IPdata.size()>0)
	{
		// std::cout<<"Sending message to all\t" <<message<<"\n";
		IPMessage im;
    	std::vector<pthread_t> threads= std::vector<pthread_t>(IPdata.size()-1);
		im.message=ToArr(message);
		im.sockid=sid;
		// std::cout <<"Starting for loop\n";
		for(int i=0;i<threads.size();i++)
		{
			// std::cout<<"Sending Message:"<<message<<" to:"<<IPdata[i+1].first<<std::endl;
			im.ip=IPdata[i+1].first;
			pthread_create(&threads[i],NULL,SendMessage,&im);
			usleep(1);
		}
        // std::cout<<"Messages sent!!!!!!!!!!!!!!!!!!!!!!\n";
	}
}


void* RemovePlayer(void* input)
{
	while(true)
	{
		long long now=time(0);
		for(int i=1;i<IPdata.size();i++)
		{
            if((now-TimeStamp[i])>10)
			{
                 // std::cout<<"Removing: "<<IPdata[i].first<<std::endl;
                 // std::cout<<"Time diff:"<<(now-TimeStamp[i])<<std::endl;
				if(Connect)
				{
					long long temp=IPdata[i].second;
					IPdata.erase(IPdata.begin()+i);
					TimeStamp.erase(TimeStamp.begin()+i);
					if(temp==1)
					{
						long long min=IPdata[0].first;
						int j=0;
						for(int k=1;k<IPdata.size();k++)
						{
							if(IPdata[k].first<min)
							{
								j=k;
								min=IPdata[k].first;
							}
						}
						IPdata[j].second=1;
					}
				}
			}
		}
		if(!Connect)
			break;
	}
}

void* OutMessage(void* input)
{
	long long temp=(long long)input;
	int sockid=(int)temp;
	long long count=0;
	while(true)
	{
		// std::cout<<"Sending OutMessage\n";
	    std::vector<pthread_t> threads= std::vector<pthread_t>(IPdata.size()-1);
		if(IPdata[0].second==0)
		{
			IPMessage im;
			char buf[BUFSIZE];
			sprintf(buf, "Child packet sent by:%lld %lld", IPdata[0].first,count);
			im.message=buf;
			im.sockid=sockid;
			for(int i=0;i<threads.size();i++)
			{
				// std::cout<<"Dummy:"<<ToStr(buf)<<"to: "<<IPdata[i+1].first<<std::endl;
				im.ip=IPdata[i+1].first;
				pthread_create(&threads[i],NULL,SendMessage,&im);
				usleep(1000);

			}
		}
		else
		{
			IPMessage im;
			char buf[BUFSIZE];
			sprintf(buf, "Parent packet sent by:%lld %lld", IPdata[0].first,count);
			im.message=buf;
			im.sockid=sockid;
			for(int i=0;i<threads.size();i++)
			{
				// std::cout<<"Dummy:"<<ToStr(buf)<<"to: "<<IPdata[i+1].first<<std::endl;
				im.ip=IPdata[i+1].first;
				pthread_create(&threads[i],NULL,SendMessage,&im);
				usleep(1000);
			}

		}
		if(!Connect)
			break;
		count++;
		usleep(1000000);
	}

}
void* ReceiveData(void* input)
{
	while(true)
	{
		char recvmsg[BUFSIZE];
		struct sockaddr_in myaddr, remaddr;
		socklen_t addrlen=sizeof(remaddr);
         // for(int i=0;i<IPdata.size();i++)
         //     std::cout<<IPdata[i].first<<'\t'<<IPdata[i].second<<std::endl;
         // std::cout<<"Awaiting data...\n";
		int recvlen = recvfrom(sid,recvmsg , BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if(recvmsg[0]!='0' && recvlen>0)
		{
			TimeStamp[FindIndex((long long)remaddr.sin_addr.s_addr)]=time(0);
		}
		// std::cout<<"Recieved message:"<<ToStr(recvmsg)<<" Bytes recv:"<<recvlen<<std::endl;
		if (recvlen>0) 
		{
			LastTime=time(0);
			recvmsg[recvlen] = 0;
			switch(recvmsg[0])
			{
				case '0':
				{	
					// std::cout<<"case 0\n";
					std::pair<long long,long long> p;
					// std::cout<<"case 0\n";
					p.first=(long long)remaddr.sin_addr.s_addr;
                     // std::cout<<p.first<<std::endl;
					p.second=0;
                     // std::cout<<p.second<<std::endl;
					TimeStamp.push_back(time(0));
					IPdata.push_back(p);
                     // std::cout<<time(0)<<std::endl;
                     // std::cout<<"case 0\n";
					char sendmsg[BUFSIZE];
					sendmsg[0]='1';
					sendmsg[1]=' ';
					int j=2;
					// std::cout<<"case 0\n";
					for(int i=0;i<IPdata.size()-1;i++)
					{
						char temp[20];
                        sprintf(temp,"%lld",IPdata[i].first);
                        int lenll=LengthNum(IPdata[i].first);
                        for(int k=0;k<lenll;k++)
                        {
                        	sendmsg[j]=temp[k];
                        	j++;
                        }
                        if(IPdata[i].second==1)
                        {
                        	sendmsg[j]='*';
                        	j++;
                        }
                        sendmsg[j]=' ';
                        j++;
					}
					j--;
					sendmsg[j]='\n';
					sendmsg[j+1]='\0';
//					 std::cout<<"First message sent:"<<ToStr(sendmsg);
					int slen=sizeof(remaddr);
					sendto(sid, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&remaddr, slen);
			        std::vector<pthread_t> threads= std::vector<pthread_t>(IPdata.size()-2);
			        
			        IPMessage im;
			        
			        char temp[20];
			        sprintf(temp,"%lld",(long long)remaddr.sin_addr.s_addr);
			        char sendmsg2[BUFSIZE];
			        sendmsg2[0]='2';
			        sendmsg2[1]=' ';
			        j=2;
			        for(int k=0;k<LengthNum((long long)remaddr.sin_addr.s_addr);k++)
			        {
			        	sendmsg2[j]=temp[k];
			        	j++;
			        }
			        sendmsg2[j]='\n';
			        sendmsg2[j+1]='\0';
			        im.message=sendmsg2;
			        im.sockid=sid;
                     // for(int i=0;i<IPdata.size();i++)
                         // std::cout<<IPdata[i].first<<std::endl;
			        for(int i=0;i<threads.size();i++)
			        {
//			        	 std::cout<<"sendmsg2:"<<ToStr(sendmsg2)<<"to:"<<IPdata[i+1].first<<std::endl;
			        	im.ip=IPdata[i+1].first;
			        	pthread_create(&threads[i],NULL,SendMessage,&im);
			        }
			        break;
				}
				case '2':
				{
	    	    	AddPlayers(recvmsg);
					break;
				}
				case 'C':
				{
					break;
				}
				case 'P':
				{
					break;
				}
				default:
				{	
					// Instructions.push_back(ToStr(recvmsg));
					Instructions.push(ToStr(recvmsg));
					break;
				}
			}
		}
	}

}


int networkmain(int argc, char** argv)
{
	noIP=false;
	Begin:system ("ifconfig | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -f2 -d: > .ip.txt");
	std::ifstream ip4(".ip.txt");
	std::getline(ip4,ipadr);
	std::cout<<"My IP:"<<ipadr<<std::endl;
	system("rm -rf .ip.txt");
	ip4.close();
	if(ipadr.size()==0 && !noIP)
	{
		noIP=true;
		// usleep(5000000);
		goto Begin;
	}
	if(noIP && ipadr.size()==0)
	{
		std::cout<<"Network not found. Starting an offline game.\n";
		isOffline=true;
	}
	else
	{
		isOffline=false;
	}
	char recvmsg[BUFSIZE];
	struct sockaddr_in myaddr, remaddr;
	int sockid=socket(AF_INET, SOCK_DGRAM, 0);
	sid=sockid;
	struct timeval tv;
    tv.tv_sec = 10;
	tv.tv_usec = 100000;
	if (setsockopt(sockid, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) 
	{
	    perror("Error timeout");
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(SERVICE_PORT);
	const char * ipchar = ipadr.c_str();
	inet_aton(ipchar,&myaddr.sin_addr);
	if (bind(sockid, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}    

	std::pair<long long,long long> myself;
	myself.first=(long long)(myaddr.sin_addr.s_addr);
	if(argc>1)
	{
		myself.second=0;
	}
	else
	{
		myself.second=1;
	}
	TimeStamp.push_back(time(0));
	IPdata.push_back(myself);
	if(argc>1)
	{
		playersReady=false;
	}
	else
	{
		playersReady=true;
	}
	std::cout<<"Mine:"<<myaddr.sin_addr.s_addr<<std::endl;

	memset((char *) &remaddr, 0, sizeof(remaddr));
	
	int conTo;
	if(argc>1)
	{
		START://std::cout<<"sending case 0\n";
		char sendmsg[BUFSIZE];
		remaddr.sin_family = AF_INET;
		remaddr.sin_port = htons(SERVICE_PORT);
		if(First)
		{
			if (inet_aton(argv[1], &remaddr.sin_addr)==0) 
			{
				fprintf(stderr, "inet_aton() failed\n");
			}
		}
		else
		{
			conTo=(conTo)%(IPdata.size()-2) +1;
			remaddr.sin_addr.s_addr=IPdata[conTo].first;
		}

		sendmsg[0]='0';
		sendmsg[1]=' ';
		int firstMsg=0;
		for(;firstMsg<ipadr.size();firstMsg++)
		{
			sendmsg[firstMsg+2]=ipadr[firstMsg];
		}
		sendmsg[firstMsg+2]='\n';
	
		int slen=sizeof(remaddr);
		// std::cout<<"sending data:"<<ToStr(sendmsg);
		if (sendto(sockid, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&remaddr, slen)<=0) 
		{
			perror("Sorry, player not found!\nMake sure you are connected to the network");
			goto START;
		}
		// std::cout<<"Data sent:"<<remaddr.sin_addr.s_addr<<std::endl;
		socklen_t blen=(socklen_t)slen;
		int recvlen = recvfrom(sockid, recvmsg, BUFSIZE, 0, (struct sockaddr *)&remaddr, &blen);
		// std::cout<<"First reply:"<<ToStr(recvmsg);
    	if (recvlen >= 0) 
    	{
    		for(int i=1;i<IPdata.size();i++)
			{
				IPdata.erase(IPdata.begin()+i);
				TimeStamp.erase(TimeStamp.begin()+i);
			}
    	    recvmsg[recvlen] = 0;
    	    if(recvmsg[0]=='1')
    	    	AddPlayers(recvmsg);
    	}
    	// std::cout<<"Players added\n";
    	playersReady=true;

	}

	pthread_t remplayer;
	pthread_t output;
//	pthread_create(&output,NULL,OutMessage,(void *)(long long)sockid);
	
	long long dummy=0;
	pthread_create(&remplayer,NULL, RemovePlayer,(void *)dummy);

	LastTime=time(0);
	pthread_t receive;
	pthread_create(&remplayer,NULL, ReceiveData,(void *)dummy);

	RECV:Connect=true;
	while(true)
	{	
		// socklen_t addrlen=sizeof(remaddr);
  //        for(int i=0;i<IPdata.size();i++)
  //            std::cout<<IPdata[i].first<<'\t'<<IPdata[i].second<<std::endl;
  //        std::cout<<"Awaiting data...\n";
		// int recvlen = recvfrom(sockid,recvmsg , BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		// if(recvmsg[0]!='0' && recvlen>0)
		// {
		// 	TimeStamp[FindIndex((long long)remaddr.sin_addr.s_addr)]=time(0);
		// }
		// std::cout<<"Recieved message:"<<ToStr(recvmsg)<<" Bytes recv:"<<recvlen<<std::endl;
		if ((time(0)-LastTime)>10) 
// 		{
// 			recvmsg[recvlen] = 0;
// 			switch(recvmsg[0])
// 			{
// 				case '0':
// 				{	
// 					// std::cout<<"case 0\n";
// 					std::pair<long long,long long> p;
// 					// std::cout<<"case 0\n";
// 					p.first=(long long)remaddr.sin_addr.s_addr;
//                      std::cout<<p.first<<std::endl;
// 					p.second=0;
//                      std::cout<<p.second<<std::endl;
// 					TimeStamp.push_back(time(0));
// 					IPdata.push_back(p);
//                      std::cout<<time(0)<<std::endl;
//                      std::cout<<"case 0\n";
// 					char sendmsg[BUFSIZE];
// 					sendmsg[0]='1';
// 					sendmsg[1]=' ';
// 					int j=2;
// 					// std::cout<<"case 0\n";
// 					for(int i=0;i<IPdata.size()-1;i++)
// 					{
// 						char temp[20];
//                         sprintf(temp,"%lld",IPdata[i].first);
//                         int lenll=LengthNum(IPdata[i].first);
//                         for(int k=0;k<lenll;k++)
//                         {
//                         	sendmsg[j]=temp[k];
//                         	j++;
//                         }
//                         if(IPdata[i].second==1)
//                         {
//                         	sendmsg[j]='*';
//                         	j++;
//                         }
//                         sendmsg[j]=' ';
//                         j++;
// 					}
// 					j--;
// 					sendmsg[j]='\n';
// 					sendmsg[j+1]='\0';
// //					 std::cout<<"First message sent:"<<ToStr(sendmsg);
// 					int slen=sizeof(remaddr);
// 					sendto(sockid, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&remaddr, slen);
// 			        std::vector<pthread_t> threads= std::vector<pthread_t>(IPdata.size()-2);
			        
// 			        IPMessage im;
			        
// 			        char temp[20];
// 			        sprintf(temp,"%lld",(long long)remaddr.sin_addr.s_addr);
// 			        char sendmsg2[BUFSIZE];
// 			        sendmsg2[0]='2';
// 			        sendmsg2[1]=' ';
// 			        j=2;
// 			        for(int k=0;k<LengthNum((long long)remaddr.sin_addr.s_addr);k++)
// 			        {
// 			        	sendmsg2[j]=temp[k];
// 			        	j++;
// 			        }
// 			        sendmsg2[j]='\n';
// 			        sendmsg2[j+1]='\0';
// 			        im.message=sendmsg2;
// 			        im.sockid=sockid;
//                      for(int i=0;i<IPdata.size();i++)
//                          std::cout<<IPdata[i].first<<std::endl;
// 			        for(int i=0;i<threads.size();i++)
// 			        {
// //			        	 std::cout<<"sendmsg2:"<<ToStr(sendmsg2)<<"to:"<<IPdata[i+1].first<<std::endl;
// 			        	im.ip=IPdata[i+1].first;
// 			        	pthread_create(&threads[i],NULL,SendMessage,&im);
// 			        }
// 			        break;
// 				}
// 				case '2':
// 				{
// 	    	    	AddPlayers(recvmsg);
// 					break;
// 				}
// 				case 'C':
// 				{
// 					break;
// 				}
// 				case 'P':
// 				{
// 					break;
// 				}
// 				default:
// 				{	
// 					// Instructions.push_back(ToStr(recvmsg));
// 					Instructions.push(ToStr(recvmsg));
// 					break;
// 				}
// 			}
// 		}
// 		else
		{	
			// std::cout<<"You have been disconnected\n";
			First=false;
			// pthread_join(output,NULL);
			// pthread_join(remplayer,NULL);
			// break;
			// exit(0);
			if(IPdata.size()<=2)
			{
//                 IPdata.erase(IPdata.begin()+1);
//                 TimeStamp.erase(TimeStamp.begin()+1);
				IPdata[0].second=1;
                 // std::cout<<"First GOTO\n";
				goto RECV;
			}
			else
			{
                 // std::cout<<"Second GOTO\n";
				Connect=false;
				playersReady=false;
				IPdata[0].second=0;
				pthread_join(output,NULL);
				pthread_join(remplayer,NULL);
				conTo=IPdata.size()-2;
				goto START;
			}
 		}
	}

}
