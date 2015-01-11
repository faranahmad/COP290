#include "Board.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

pthread_mutex_t UpdateLock;
Board FinalBoard;
// int counter=0

void *UpdateBoardThread(void* id)
{
	while (true)
	{
		long ballid = (long) id;
		pthread_mutex_lock (&UpdateLock);
		cout <<"Starting for ball " <<ballid<<"\n";
		Ball BallConsidered = FinalBoard.GetBallFromId(ballid);
		int BallConsidered_Coordx = BallConsidered.GetX();
		int BallConsidered_Coordy = BallConsidered.GetY();
		int BallConsidered_VelocityX=BallConsidered.GetVelocityX();
		int BallConsidered_VelocityY=BallConsidered.GetVelocityY();
		BallConsidered.SetX(((BallConsidered_Coordx+BallConsidered_VelocityX)%(2*FinalBoard.GetDimensionX())) -FinalBoard.GetDimensionX());
		BallConsidered.SetY(((BallConsidered_Coordy+BallConsidered_VelocityY)%(2*FinalBoard.GetDimensionY())) -FinalBoard.GetDimensionY());
		FinalBoard.SetBallFromId(ballid,BallConsidered);
		pthread_mutex_unlock (&UpdateLock);	
		usleep(100000);
	}
}	

int main(int argc, char **argv)
{
	const int NumberOfBalls = atoi(argv[1]);
	pthread_mutex_init(&UpdateLock,NULL);
	FinalBoard=Board(1600,900,NumberOfBalls);
	pthread_t BallThreads [NumberOfBalls];
	std::cout <<"Ball threas" <<NumberOfBalls <<"\n";
	for (long i=0; i<NumberOfBalls ;i++)
	{
		cout <<"Creating thread i: " <<i <<"\n";
		pthread_create(&BallThreads[i],NULL,UpdateBoardThread,(void *)i);
	
	}	
	for (int i=0; i<NumberOfBalls ;i++)
	{
		pthread_join(BallThreads[i],NULL);
	}
	// create a display thread 
	// run the threads 
	pthread_exit(NULL);
	return 0;
}