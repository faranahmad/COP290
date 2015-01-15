Compiler= g++
Arguments= -std=c++11 
Including= -lpthread
IncludingGraphics= -lGL -lGLU -lglut
alpha=3

all: Ball.cpp Board.cpp Threads.cpp  
	$(Compiler) $(Arguments) Ball.cpp Board.cpp Threads.cpp  $(Including)

execute: Ball.cpp Board.cpp Image.cpp Color.cpp Threads.cpp
	$(Compiler) $(Arguments) Color.cpp Ball.cpp Board.cpp Image.cpp Threads.cpp $(Including) $(IncludingGraphics)
	./a.out $(num_thread)

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 

clean:
	rm a.out
