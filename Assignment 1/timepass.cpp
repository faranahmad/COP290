#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
#define N 2  /* # of thread */

int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};  /* target array */
int sum=0;
/* structure for array index
 * used to keep low/high end of sub arrays
 */
struct Arr {
    int low;
    int high;
};

/*void sum1(int low, int high)
{

        int mid = (low+high)/2;
        int left = low;
        int right = mid+1;



        while(left <= mid && right <= high) {
        //something to be added
         }

        //while(left <= mid) sum += a[left];
        //while(right <= high) sum += a[right];
        // for (i = 0; i < (high-low+1) ; i++) a[low+i] = b[i];
}
*/
void * sum(void *a)
{
        Arr *pa = (Arr *)a;
        int mid = (pa->low + pa->high)/2;

        Arr aIndex[N];
        pthread_t thread[N];

        aIndex[0].low = pa->low;
        aIndex[0].high = mid;

        aIndex[1].low = mid+1;
        aIndex[1].high = pa->high;

        if (pa->low >= pa->high) 
            return;

        int i;
        for(i = 0; i < N; i++) pthread_create(&thread[i], NULL, sum, &aIndex[i]);
        for(i = 0; i < N; i++) pthread_join(thread[i], NULL);

        sum1(pa->low, pa->high);

        pthread_exit(NULL);
}

int main()
{
        Arr ai;
        ai.low = 0;
        ai.high = sizeof(a)/sizeof(a[0])-1;
        pthread_t thread;

        pthread_create(&thread, NULL, sum, &ai);
        pthread_join(thread, NULL);
        cout << sum;
        return 0;
}