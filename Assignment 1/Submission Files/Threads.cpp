#include "Board.h"
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t UpdateLock;
Board FinalBoard;
// int counter=0

void *UpdateBoardThread(void* id)
{
	long ballid= (long) id;
	pthread_mutex_lock (&UpdateLock);
	
	// Updating functions go here

	pthread_mutex_unlock (&UpdateLock);
}

int main(int argc, char **argv)
{
	const int NumberOfBalls = argc -1;

	FinalBoard=Board(1600,900,NumberOfBalls);



	// Create new board with number of Balls 
	// Each ball  has a random position, random speed, random color
	// initialise threads for the balls 
	// create a display thread 
	// run the threads 
	
	return 0;
}