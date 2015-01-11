Compiler= g++
Arguments= -std=c++11 
Including= -lpthread
IncludingGraphics= -lGL -lGLU -lglut

all: Ball.cpp Board.cpp Threads.cpp  
	$(Compiler) $(Arguments) Ball.cpp Board.cpp Threads.cpp  $(Including)

graphics: Ball.cpp Board.cpp Threads.cpp Graphics.cpp
	$(Compiler) $(Arguments) Ball.cpp Board.cpp Threads.cpp $(Including) $(IncludingGraphics)

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 

clean:
	rm a.out
