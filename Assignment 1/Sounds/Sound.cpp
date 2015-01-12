#include <curses.h>
#include <stdio.h>

int main()
{
	char d=(char)(7);
	for (int i=0;i<10000;i++)
	{
		//beep();
		printf("%c\n",d);
	}
	return 0;
}
