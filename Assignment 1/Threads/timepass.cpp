#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
#define N 2  /* # of thread */

int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};  /* target array */
// int arr[] ={1,2};

int globalsum;
//int sum=0;
/* structure for array index
 * used to keep low/high end of sub arrays
 */
struct Arr {
    int low;
    int high;
};

// int sum1(int low, int high)
// {
//     int mid = (low+high)/2;
//     int left = low;
//     int right = mid+1;
//     if (low >= high)
//     {
//         return [low];
//     }
//     else 
//         return sum1(low,mid) + sum1(mid+1,right);
//     //while
//     //(left <= mid) sum += a[left];
//     //while(right <= high) sum += a[right];
//     // for (i = 0; i < (high-low+1) ; i++) a[low+i] = b[i];
// }

void * sum(void *a)
{
    Arr *pa =(Arr *)a;
    cout <<(pa->low)<<"\t"<<(pa->high)<<"\n";
    if (pa->low +1 == pa->high)
    {   
        globalsum+=arr[pa->low];
    }
    else
    {
        int mid=(pa->low+pa->high)/2;
        Arr aIndex[N];
        pthread_t thread[N];
        aIndex[0].low = pa->low;
        aIndex[0].high = mid;
        aIndex[1].low = mid;
        aIndex[1].high = pa->high;
        for (int i=0; i<N ; i++)
        {
            pthread_create(&thread[i], NULL, sum, &aIndex[i]);
        }
        for (int j=0; j<N;j++)
        {
            pthread_join(thread[j],NULL);
        }
        pthread_exit(NULL);
    }

    // Arr *pa = (Arr *)a;
    // int mid = (pa->low + pa->high)/2;
    // Arr aIndex[N];
    // pthread_t thread[N];
    // aIndex[0].low = pa->low;
    // aIndex[0].high = mid;
    // aIndex[1].low = mid+1;
    // aIndex[1].high = pa->high;
    // if (pa->low >= pa->high) 
    //     return (void *)2;
    // int i;
    // for(i = 0; i < N; i++) pthread_create(&thread[i], NULL, sum, &aIndex[i]);
    // for(i = 0; i < N; i++) pthread_join(thread[i], NULL);
    // sum1(pa->low, pa->high);
    // pthread_exit(NULL);
}

int main()
{
    globalsum=0;
    Arr ai;
    ai.low = 0;
    ai.high = sizeof(arr)/sizeof(arr[0]);
    pthread_t thread;
    pthread_create(&thread, NULL, sum, &ai);
    pthread_join(thread, NULL);
    cout <<globalsum<<" this is the answer\n";
    pthread_exit(NULL);
    return 0;
}