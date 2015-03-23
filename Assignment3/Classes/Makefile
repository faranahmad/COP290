all: Game Test

RunGame: Game
	./Game

RunTest: Test
	./Test

Game: Alien.o Ship.o Color.o Bullet.o Board.o Combined.o
	g++ -o Game Color.o Ship.o Bullet.o Alien.o Board.o Combined.o -lGL -lGLU -lglut

Test: Test.o Alien.o Ship.o Color.o Bullet.o Board.o ShipTest.o AllTests.o
	g++ -o Test Test.o Alien.o Ship.o Color.o Bullet.o Board.o ShipTest.o AllTests.o

Color.o: Color.cpp
	g++ -c Color.cpp

Alien.o: Alien.cpp
	g++ -c Alien.cpp

Ship.o: Ship.cpp
	g++ -c Ship.cpp

Bullet.o: Bullet.cpp
	g++ -c Bullet.cpp

Board.o: Board.cpp
	g++ -c Board.cpp

Combined.o: Combined.cpp
	g++ -c Combined.cpp

Test.o: Test.cpp
	g++ -c Test.cpp

ShipTest.o: ShipTest.cpp
	g++ -c ShipTest.cpp

AllTests.o: AllTests.cpp
	g++ -c AllTests.cpp

clean:
	rm -rf *.o
	rm -rf Test Game
