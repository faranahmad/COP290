ver = -std=c++11

all: Game Test

RunGame: Game
	./Game $(ip)

RunTest: Test
	./Test

Game: Alien.o Ship.o Color.o Bullet.o Board.o udp.o Combined.o
	g++ $(ver) -o Game Color.o Ship.o Bullet.o Alien.o Board.o udp.o Combined.o -lGL -lGLU -lglut -lpthread


Color.o: Color.cpp
	g++ $(ver) -c Color.cpp

Alien.o: Alien.cpp
	g++ $(ver) -c Alien.cpp

Ship.o: Ship.cpp
	g++ $(ver) -c Ship.cpp

Bullet.o: Bullet.cpp
	g++ $(ver) -c Bullet.cpp

Board.o: Board.cpp
	g++ $(ver) -c Board.cpp

AI.o: AI.cpp
	g++ $(ver) -c AI.cpp

udp.o: udp.cpp
	g++ $(ver) -c udp.cpp

Combined.o: Combined.cpp
	g++ $(ver) -c Combined.cpp

GameDebug: AlienD.o ShipD.o ColorD.o BulletD.o BoardD.o AID.o udpD.o CombinedD.o
	g++ $(ver) -o GameDebug ColorD.o ShipD.o BulletD.o AlienD.o BoardD.o AID.o udpD.o CombinedD.o -g -lGL -lGLU -lglut -lpthread

Test: Test.o Alien.o Ship.o Color.o Bullet.o Board.o ShipTest.o AllTests.o
	g++ $(ver) -o Test Test.o Alien.o Ship.o Color.o Bullet.o Board.o ShipTest.o AllTests.o

ColorD.o: Color.cpp
	g++ $(ver) -c Color.cpp -g

AlienD.o: Alien.cpp
	g++ $(ver) -c Alien.cpp -g

ShipD.o: Ship.cpp
	g++ $(ver) -c Ship.cpp -g

BulletD.o: Bullet.cpp
	g++ $(ver) -c Bullet.cpp -g

BoardD.o: Board.cpp
	g++ $(ver) -c Board.cpp -g

AID.o: AI.cpp
	g++ $(ver) -c AI.cpp -g

udpD.o: udp.cpp
	g++ $(ver) -c udp.cpp -g

CombinedD.o: Combined.cpp
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
