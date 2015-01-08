#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t myMutex1,myMutex2,myMutex3;
void *print1(void * x)
{
	for(int i = 0;i<4;i++)
	{
		pthread_mutex_lock(&myMutex1);
		cout << "faran is genius"<< endl;
		sleep(1);
		
	}
	pthread_mutex_unlock(&myMutex1);
	//pthread_exit(NULL);
}
void *print2(void * x)
{
	for(int i = 0;i<5;i++)
	{
		pthread_mutex_lock(&myMutex2);
		cout << "prateek is chutiya"<< endl;
		sleep(1);
		
	}
	pthread_mutex_unlock(&myMutex2);
	//pthread_exit(NULL);
}
void *print3(void * x)
{
	for(int i = 0;i<6;i++)
	{
		pthread_mutex_lock(&myMutex3);
		cout << "kg is domestic violence ka shikaar"<< endl;
		sleep(1);
		
	}
	pthread_mutex_unlock(&myMutex3);
	//pthread_exit(NULL);
}

int main()
{
	pthread_t thread1,thread2,thread3;
	pthread_mutex_init(&myMutex1,NULL);
	pthread_create(&thread1, NULL,print1, NULL);
	pthread_join(thread1,NULL);
	pthread_mutex_destroy(&myMutex1);
	pthread_mutex_init(&myMutex2,NULL);
	pthread_create(&thread2, NULL,print2, NULL);
	pthread_join(thread2,NULL);
	pthread_mutex_destroy(&myMutex2);
	pthread_mutex_init(&myMutex3,NULL);
	pthread_create(&thread3, NULL,print3, NULL);
	
	
	pthread_join(thread3,NULL);
	//pthread_exit(NULL);
	
	
	pthread_mutex_destroy(&myMutex3);
	return 0;
}