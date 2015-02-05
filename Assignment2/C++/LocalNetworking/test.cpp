#include <iostream>

using namespace std;

int main()
{
    cout <<"starting\n";
    char *xyz = new char[999000000];
    cout  << "array created\n";
    for (long i=0; i<999000000; i++)
    {
        xyz[i]='a';
    }
    cout <<"done with this\n";
    return 0;
}
