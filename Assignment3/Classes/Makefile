ver = -std=c++11

all: Game Test

RunGame: Game
	./Game $(ip)

RunTest: Test
	./Test

Game: Alien.o Ship.o Color.o Bullet.o Board.o AI.o udp.o Combined.o
	g++ $(ver) -o Game Color.o Ship.o Bullet.o Alien.o Board.o AI.o udp.o Combined.o -g -lGL -lGLU -lglut -lpthread

Test: Test.o Alien.o Ship.o Color.o Bullet.o Board.o ShipTest.o AllTests.o
	g++ $(ver) -o Test Test.o Alien.o Ship.o Color.o Bullet.o Board.o ShipTest.o AllTests.o

Color.o: Color.cpp
	g++ $(ver) -c Color.cpp -g

Alien.o: Alien.cpp
	g++ $(ver) -c Alien.cpp -g

Ship.o: Ship.cpp
	g++ $(ver) -c Ship.cpp -g

Bullet.o: Bullet.cpp
	g++ $(ver) -c Bullet.cpp -g

Board.o: Board.cpp
	g++ $(ver) -c Board.cpp -g

AI.o: AI.cpp
	g++ $(ver) -c AI.cpp -g

udp.o: udp.cpp
	g++ $(ver) -c udp.cpp -g

Combined.o: Combined.cpp
	g++ $(ver) -c Combined.cpp -g

Test.o: Test.cpp
	g++ $(ver) -c Test.cpp

ShipTest.o: ShipTest.cpp
	g++ $(ver) -c ShipTest.cpp

AllTests.o: AllTests.cpp
	g++ $(ver) -c AllTests.cpp

clean:
	rm -rf *.o
	rm -rf Test Game
