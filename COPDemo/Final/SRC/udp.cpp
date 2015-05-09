#include "udp.h"      

std::vector< std::pair<long long,long long> > IPdata; //Keeping IP data. First element is ip address and second is wether it is the virtual server or not.
std::vector<long long>TimeStamp; //Time stamp of last received data corresponding to the IPdata
std::queue<std::string> Instructions; //Queue of instructions to be executed


bool First=true; //Connecting for the first time
bool Connect; //Status of the connection
bool playersReady; //Other players are ready or not
bool isOffline; //Whether the game is online or offline
bool noIP;//No IP obtained

int TotalPlayers=0; //Net total players connected
std::string ipadr; //String for storing the IP address

int sid; //sockid
int LastTime;//Last time stamp at which data was received

struct IPMessage { //Structure used to interact with other IPs
    long long ip;
    char* message;
    int sockid;
};

std::string GetIP() //Returns the IP of the player
{
	return ipadr;
}
bool IsBaap() //Returns whether the player is the 'virtual server' or not
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

std::string ToStr(char* arr)  //Converts a char* to string
{
    std::string ans="";
    for(int i=0;i<strlen(arr)&&arr[i]!='\0';i++)
    {
        ans+=arr[i]; //adding element one by one
    }
    return ans;
}

int GetNumPlayers() //Returns the total number of players
{
	return TotalPlayers;
}

void PrintCurrentIP() //Print current status of all the connected IPs
{
	for(int i=0;i<IPdata.size();i++)
	{
		std::cout<<IPdata[i].first<<'\t'<<IPdata[i].second<<'\t'<<TimeStamp[i]<<std::endl;
	}
}

void AddPlayers(char players []) //Adding players to the IPdata
{
	std::string s;
    int i;
	for(i=2;players[i]!=0;i++)
	{
		if(players[i]=='@') //Last character
		{
			break;
		}
		else if(players[i]!=' ' && players[i]!='\n')
		{
			s=s+players[i];
		}
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
			TimeStamp.push_back(time(0));
			IPdata.push_back(p);
			s="";
		}
	}
	int t=(int)(players[i+1]);
	int u=(int)('0');
	if (TotalPlayers==1)
	{
		TotalPlayers= t-u;
	}
}

int LengthNum(long long num) //Return the length of a long long int
{
	int ans=0;
	while(num>0)
	{
		num=num/10;
		ans++;
	}
	return ans;
}

int FindIndex(long long ip) //Finds the index of the given IP in the IPdata vector
{
	for(int i=0;i<IPdata.size();i++)
	{
		if(IPdata[i].first==ip)
			return i;
	}
	return -1;
}

//Threadable function which sends data to a particular ip
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
    if(FindIndex((long long)remaddr.sin_addr.s_addr)>0)
    {	
		int bytes_sent=sendto(sockid, message, strlen(message), 0, (struct sockaddr *)&remaddr, slen);
	} 
	pthread_exit(NULL);
}

char* ToArr(std::string str)  //Converts string to char* for sending data
{
    char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
	delete [] cstr;
}

void SendMessageToAll(std::string message) //Send a particular string(data) to all the connected IPs
{
	if(IPdata.size()>0)
	{
		IPMessage im;
    	std::vector<pthread_t> threads= std::vector<pthread_t>(IPdata.size()-1);
		im.message=ToArr(message);
		im.sockid=sid;
		for(int i=0;i<threads.size();i++)
		{
			im.ip=IPdata[i+1].first;
			pthread_create(&threads[i],NULL,SendMessage,&im);
			usleep(1);
		}
	}
}

//This function removes connection for all those IP 
//from which data has not been received for 6 seconds
void* RemovePlayer(void* input) 
{
	while(true)
	{
		long long now=time(0);
		for(int i=1;i<IPdata.size();i++)
		{
            if((now-TimeStamp[i])>10) //No data received for last 6 seconds
			{
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

//This message was used in the testing of the network design
//It sends dummy messages to all the other IPs
void* OutMessage(void* input)
{
	long long temp=(long long)input;
	int sockid=(int)temp;
	long long count=0;
	while(true)
	{
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

//Processing the received data
//Adds new players to the game
//'0','1' and '2' opcodes are used to initiate the game
//Other messages are pushed into the Instructions queue
void* ReceiveData(void* input)
{
	while(true)
	{
		char recvmsg[BUFSIZE];
		struct sockaddr_in myaddr, remaddr;
		socklen_t addrlen=sizeof(remaddr);
		int recvlen = recvfrom(sid,recvmsg , BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if(recvmsg[0]!='0' && recvlen>0)
		{
			TimeStamp[FindIndex((long long)remaddr.sin_addr.s_addr)]=time(0);
		}
		if (recvlen>0) 
		{
			LastTime=time(0);
			recvmsg[recvlen] = 0;
			switch(recvmsg[0])
			{
				case '0': //New player has been added.
						  //Send the new player IPs of all other players
						  //Send the other players IP of the new player
				{	
					std::pair<long long,long long> p;
					p.first=(long long)remaddr.sin_addr.s_addr;
					p.second=0;
					TimeStamp.push_back(time(0));
					IPdata.push_back(p);
					TotalPlayers++;
					char sendmsg[BUFSIZE];
					sendmsg[0]='1';
					sendmsg[1]=' ';
					int j=2;
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
					sendmsg[j]='@';
					sendmsg[j+1]=(char)(TotalPlayers+int('0'));
					sendmsg[j+2]='\n';
					sendmsg[j+3]='\0';
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
			        for(int i=0;i<threads.size();i++)
			        {
			        	im.ip=IPdata[i+1].first;
			        	pthread_create(&threads[i],NULL,SendMessage,&im);
			        }
			        break;
				}
				case '2': //Add New player to the game
				{
	    	    	AddPlayers(recvmsg);
					break;
				}
				case 'C'://Child packet
				{
					break;
				}
				case 'P'://Parent packet
				{
					break;
				}
				default: //Add the message to Instructions queue
				{	
					Instructions.push(ToStr(recvmsg));
					break;
				}
			}
		}
	}

}

//Network main
int networkmain(int argc, char** argv)
{
	noIP=false; //Getting IP of the computer
	Begin:system ("ifconfig | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -f2 -d: > .ip.txt");
	std::ifstream ip4(".ip.txt");
	std::getline(ip4,ipadr);
	std::cout<<"My IP:"<<ipadr<<std::endl;
	system("rm -rf .ip.txt");
	ip4.close();
	if(ipadr.size()==0 && !noIP)
	{
		noIP=true;
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
	int sockid=socket(AF_INET, SOCK_DGRAM, 0); //Setting up socket
	sid=sockid;
	struct timeval tv;
    tv.tv_sec = 10; //Setting the timeout for the socket
	tv.tv_usec = 100000;
	if (setsockopt(sockid, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) 
	{
	    perror("Error timeout");
	}

	//setting up structure
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

	//Adding myself to the IPdata
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
	TotalPlayers++;
	if(argc>1)
	{
		playersReady=false;
	}
	else
	{
		playersReady=true;
	}

	memset((char *) &remaddr, 0, sizeof(remaddr));
	
	int conTo;
	if(argc>1)
	{
		START://connecting for the first time
        std::cout << "In goto\n";
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
		//sending my IP to the game
		sendmsg[0]='0';
		sendmsg[1]=' ';
		int firstMsg=0;
		for(;firstMsg<ipadr.size();firstMsg++)
		{
			sendmsg[firstMsg+2]=ipadr[firstMsg];
		}
		sendmsg[firstMsg+2]='\n';
	
        std::cout <<"sent ipdata\n";
		//Receiving data for the first time
		int slen=sizeof(remaddr);
		if (sendto(sockid, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&remaddr, slen)<=0) 
		{
			perror("Sorry, player not found!\nMake sure you are connected to the network");
			goto START;
		}
		socklen_t blen=(socklen_t)slen;
		int recvlen = recvfrom(sockid, recvmsg, BUFSIZE, 0, (struct sockaddr *)&remaddr, &blen);
    	if (recvlen >= 0) 
    	{
    		//Removing old players 
    		for(int i=1;i<IPdata.size();i++)
			{
				IPdata.erase(IPdata.begin()+i);
				TimeStamp.erase(TimeStamp.begin()+i);
			}
			//Adding players
    	    recvmsg[recvlen] = 0;
    	    if(recvmsg[0]=='1')
    	    	AddPlayers(recvmsg);
    	}
    	playersReady=true;
	}

	pthread_t remplayer;
	pthread_t output;
	//pthread_create(&output,NULL,OutMessage,(void *)(long long)sockid);
	Connect=true;
	long long dummy=0;

	//Initiating RemovePlayer function
	pthread_create(&remplayer,NULL, RemovePlayer,(void *)dummy);

	LastTime=time(0);
	pthread_t receive;

	//Initiating RecieveData function
	pthread_create(&remplayer,NULL, ReceiveData,(void *)dummy);

	RECV:dummy++;
	while(true)
	{	
        if ((time(0)-LastTime)>6)

		{	
			First=false;
			if(IPdata.size()<=2)
			{
				IPdata[0].second=1;
				goto RECV;
			}
			else
            {
                std::cout<<"here\n"<<std::endl;
				Connect=false;
				playersReady=false;
				IPdata[0].second=0;
//                pthread_join(remplayer,NULL);
                conTo=IPdata.size()-2;
                std::cout <<"Now going to goto\n";
                goto START;
			}
 		}
	}
}
