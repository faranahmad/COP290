#include "login.h"
#include "Client.h"
#include <QApplication>
#include "main.h"
#include <pthread.h>

void *StartBackend(void *xyz)
{
	int p1=clientmain();
}

bool windowshow = true;
int main(int argc, char *argv[])
{
	pthread_t threads[2];
	// bool contains=false;
	// bool buttonclicked=false;
    
    contains=false;
    buttonclicked=false;
    usname="";
    passwd="";

    pthread_create(&threads[0],NULL,StartBackend,NULL);

    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
