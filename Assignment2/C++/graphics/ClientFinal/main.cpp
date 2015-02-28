#include "login.h"
#include <QApplication>
#include "ClientCombined.h"
bool windowshow = true;

struct graph
{
	int argcx;
	char** argvy;
};

bool InstructionStarted, InstructionCompleted;
std::string reversedata1,reversedata2,reversedata3;
std::string inst, datafield1, datafield2, datafield3;
SyncManager MergedSyncManager;

void *StartBackend(void *xyz)
{
    graph *ps=(graph *) xyz;
	clientmain(ps->argcx,ps->argvy);
	return (void *) 1;
}



int main(int argc, char *argv[])
{
	pthread_t BackEndThread;

	InstructionStarted=false;
	InstructionCompleted=false;
	datafield1="";
	datafield2="";
	datafield3="";
	reversedata1="";
	reversedata2="";
	reversedata3="";
	inst="";
	MergedSyncManager=SyncManager();

    graph data;
    data.argcx=argc;
    data.argvy=argv;

    pthread_create(&BackEndThread,NULL,StartBackend,&data);

    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
