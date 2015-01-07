#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

vector<int> v1;
vector<int> s1;

int gsum;
vector<bool> truthvalues;


void *PrintHello(void *threadid)
{
   long tid= (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}

void *AddElements(void *start)
{
	long start1=(long) start;
	for (int j=10*start1;j<(1+start1)*10;j++)
	{
		s1[start1] += v1[j];
	}
	cout <<s1[start1]<<"\t"<<start1<<"\n";
	truthvalues[start1]=true;
	gsum +=s1[start1];
	pthread_exit(NULL);
}

// void *VerifyDone

int main ()
{
   pthread_t threads[5];
   int rc;
   for (int m=0;m<40;m++)
   {
   		v1.push_back(2*m);
   }
   s1.push_back(0);
   s1.push_back(0);
   s1.push_back(0);
   s1.push_back(0);
   gsum=0;
   truthvalues.push_back(false);
   truthvalues.push_back(false);
   truthvalues.push_back(false);
   truthvalues.push_back(false);
   for( int i=0; i < 4; i++ )
   {
      cout << "main() : creating thread, " << i << endl;
      rc= pthread_create(&threads[i], NULL,AddElements, (void *)i);
   }
   for (int i=0;i<4;i++)
   {
   		pthread_join(threads[i],NULL);
   }
   // rc=pthread_create(&threads[4],NULL, VerifyDone,)
   cout <<s1[0]<<"\t"<<s1[1]<<"\t"<<s1[2]<<"\t"<<s1[3]<<" is the vect\n";
   cout << s1[0]+s1[1]+s1[2]+s1[3]<<" is the ans\n";
   pthread_exit(NULL);
   return 0;
}