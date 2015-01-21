Compiler= g++
Arguments= -std=c++11 
Mode= -c
Including= -lpthread
IncludingGraphics= -lGL -lGLU -lglut
alpha=3

all: 3D

3D: Color.o Ball.o Board.o Image.o Threads.o
	$(Compiler) $(Arguments) $(Including) $(IncludingGraphics) Color.o Ball.o Board.o Image.o Threads.o -o 3DEverything

Color.o: Color.cpp
	$(Compiler) $(Mode) $(Arguments) Color.cpp

Ball.o: Color.o Ball.cpp 
	$(Compiler) $(Arguments) $(Mode) Color.cpp Ball.cpp

Board.o: Ball.o Board.cpp 
	$(Compiler) $(Arguments) $(Mode) Color.cpp Ball.cpp Board.cpp

Image.o: Image.cpp
	$(Compiler) $(Mode) $(Arguments) $(IncludingGraphics) Image.cpp

Threads.o: Image.o Board.o Threads.cpp
	$(Compiler) $(Arguments) $(Including) $(IncludingGraphics) $(Mode)  Image.cpp Color.cpp Ball.cpp Board.cpp Threads.cpp

execute: Ball.cpp Board.cpp Image.cpp Color.cpp Threads.cpp
	$(Compiler) $(Arguments) Color.cpp Ball.cpp Board.cpp Image.cpp Threads.cpp $(Including) $(IncludingGraphics)
	./a.out $(num_thread)
	rm a.out 

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 
	rm a.out 
	
clean:
	rm a.out
