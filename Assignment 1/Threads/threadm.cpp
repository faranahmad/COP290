#include <iostream>
#include <pthread.h>
// #include <unistd.h>

using namespace std;

pthread_mutex_t mutexsum;
int gCount=0;

void *odd(void* ptr)
{
while(gCount<=10)
{
   if(gCount%2==1) //If even
   {
        pthread_mutex_lock (&mutexsum);
        gCount++;
        cout<<"faran is great"<<endl;
        sleep(1);
        pthread_mutex_unlock (&mutexsum);
   }
}
}

void *even(void* ptr)
{
  while(gCount<10)
  {
     if(gCount%2==0) //If even
     {
          pthread_mutex_lock (&mutexsum);
          gCount++;
          std::cout<<"kartikeya is domestic violence ka shikaar"<<endl;
          sleep(1);
          pthread_mutex_unlock (&mutexsum);
     }
  }

}

int main()
{

    pthread_t T_even, T_odd;
    int T_rt1,T_rt2;
    void *status;
    pthread_mutex_init(&mutexsum, NULL);
    int i=0; 
    T_rt1= pthread_create(&T_odd,NULL,odd,&i); 
    T_rt2=pthread_create(&T_even,NULL,even,&i);

    pthread_join(T_odd,&status);
    pthread_join(T_even,&status);

    pthread_exit(NULL);
    return 0;
}