Compiler=g++
Arguments= -std=c++11 
Including= -lpthread

all: Ball.cpp Board.cpp Threads.cpp  
	$(Compiler) $(Arguments) $(Including) Ball.cpp Board.cpp Threads.cpp  

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 

clean:
	rm a.out
