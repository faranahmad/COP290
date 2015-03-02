#include "server.h"
#include <QApplication>
#include <vector>
#include <string>
#include "Server2.h"
#include <iostream>

std::vector<std::string> listofitems;

struct graph
{
	int argcx;
	char** argvy;
};

void *StartBackend(void *xyz)
{
    graph *ps=(graph *) xyz;
	servermain(ps->argcx,ps->argvy);
	return (void *) 1;
}

std::string porttodisplay;
std::string iptodisplay;
std::vector<std::string> usersLog;
char input;



 int main(int argc, char *argv[])
{
	if (argc<3)
	{
		std::cout << "Usage: ./server ipaddress port\n"; 
	}
	else
	{
		porttodisplay=(argv[2]);
		iptodisplay = (argv[1]);
		listofitems = std::vector<std::string> ();
	
		pthread_t BackEndThread;
	
	    graph data;
	    data.argcx=argc;
	    data.argvy=argv;
	
	    pthread_create(&BackEndThread,NULL,StartBackend,&data);
	
	    QApplication a(argc, argv);
	    server w;
	    w.show();
    	for (int i = 0;i<100;i++)
        	 listofitems.push_back(std::to_string(i));

    	return a.exec();
    }
}
