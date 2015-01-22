Compiler= g++
Arguments= -std=c++11 
Mode= -c
Including= -lpthread
IncludingGraphics= -lGL -lGLU -lglut

all: 3D
	3D $(num_thread)

3D: Color.o Ball.o Board.o Image.o Threads.o
	$(Compiler) $(Arguments) -o 3D ObjectFiles/Color.o ObjectFiles/Ball.o ObjectFiles/Board.o ObjectFiles/Image.o ObjectFiles/Threads.o $(Including) $(IncludingGraphics) 
	
	# $(Compiler) $(Arguments) Color.cpp Ball.cpp Board.cpp Image.cpp Threads.cpp $(Including) $(IncludingGraphics)
	
Color.o: Color.cpp
	$(Compiler) $(Mode) $(Arguments)  Color.cpp 
	mv Color.o ObjectFiles/Color.o

Ball.o: ObjectFiles/Color.o Ball.cpp 
	$(Compiler) $(Mode) $(Arguments) Color.cpp Ball.cpp 
	mv Ball.o ObjectFiles/Ball.o

Board.o: ObjectFiles/Color.o ObjectFiles/Ball.o Board.cpp 
	$(Compiler) $(Mode) $(Arguments) Color.cpp Ball.cpp Board.cpp 
	mv Board.o ObjectFiles/Board.o

Image.o: Image.cpp
	$(Compiler) $(Mode) $(Arguments) $(IncludingGraphics) Image.cpp
	mv Image.o ObjectFiles/Image.o

Threads.o: Image.o Color.o Ball.o Board.o Threads.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics) Image.cpp Color.cpp Ball.cpp Board.cpp Threads.cpp
	mv Threads.o ObjectFiles/Threads.o

execute: Ball.cpp Board.cpp Image.cpp Color.cpp Threads.cpp
	$(Compiler) $(Arguments) Color.cpp Ball.cpp Board.cpp Image.cpp Threads.cpp $(Including) $(IncludingGraphics)
	./a.out $(num_thread)
	rm a.out 

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 
	rm a.out 
	
clean:
	rm -rf ObjectFiles/*.o 3D
	rm -rf *.o 3D
	rm -rf a.out
