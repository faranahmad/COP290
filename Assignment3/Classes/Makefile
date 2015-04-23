ver = -std=c++11

all: Game CompGame Test

RunGame: Game
	./Game $(ip) $(name)

RunCompGame: CompGame
	./CompGame $(ip) $(name)

RunTest: Test
	./Test

Game: Alien.o Ship.o Color.o Bullet.o Board.o AIcomputation.o AIalien.o AIMissile.o AIPlayer.o AIUpdate.o udp.o Image.o Highscore.o Combined.o
	g++ $(ver) -o Game Color.o Ship.o Bullet.o Alien.o Board.o AIcomputation.o AIalien.o AIMissile.o AIPlayer.o AIUpdate.o udp.o Image.o Highscore.o Combined.o -lGL -lGLU -lglut -lpthread

CompGame: Alien.o Ship.o Color.o Bullet.o CompetitiveBoard.o OPAIcomputation.o OPAIMissile.o OPAIPlayer.o OPAIUpdate.o udp.o Image.o Highscore.o  CompCombined.o
	g++ $(ver) -o CompGame Color.o Ship.o Bullet.o Alien.o CompetitiveBoard.o OPAIcomputation.o OPAIMissile.o OPAIPlayer.o OPAIUpdate.o udp.o Image.o Highscore.o  CompCombined.o -lGL -lGLU -lglut -lpthread

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

CompetitiveBoard.o: CompetitiveBoard.cpp
	g++ $(ver) -c CompetitiveBoard.cpp

AIcomputation.o: AIcomputation.cpp
	g++ $(ver) -c AIcomputation.cpp

AIalien.o: AIalien.cpp
	g++ $(ver) -c AIalien.cpp

AIMissile.o: AIMissile.cpp
	g++ $(ver) -c AIMissile.cpp

AIPlayer.o: AIPlayer.cpp
	g++ $(ver) -c AIPlayer.cpp

AIUpdate.o: AIUpdate.cpp
	g++ $(ver) -c AIUpdate.cpp

OPAIcomputation.o: OPAIcomputation.cpp
	g++ $(ver) -c OPAIcomputation.cpp

OPAIMissile.o: OPAIMissile.cpp
	g++ $(ver) -c OPAIMissile.cpp

OPAIPlayer.o: OPAIPlayer.cpp
	g++ $(ver) -c OPAIPlayer.cpp

OPAIUpdate.o: OPAIUpdate.cpp
	g++ $(ver) -c OPAIUpdate.cpp

AI.o: AI.cpp
	g++ $(ver) -c AI.cpp

udp.o: udp.cpp
	g++ $(ver) -c udp.cpp

Image.o: Image.cpp
	g++ $(ver) -c Image.cpp

Highscore.o: Highscore.cpp
	g++ $(ver) -c Highscore.cpp

Combined.o: Combined.cpp
	g++ $(ver) -c Combined.cpp

CompCombined.o: CompCombined.cpp
	g++ $(ver) -c CompCombined.cpp

GameDebug: AlienD.o ShipD.o ColorD.o BulletD.o BoardD.o AIcomputationD.o AIalienD.o AIMissileD.o AIPlayerD.o AIUpdateD.o udpD.o ImageD.o HighscoreD.o CombinedD.o
	g++ $(ver) -o Game Color.o Ship.o Bullet.o Alien.o Board.o AIcomputation.o AIalien.o AIMissile.o AIPlayer.o AIUpdate.o udp.o Image.o Highscore.o Combined.o -g -lGL -lGLU -lglut -lpthread

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

CompetitiveBoardD.o: CompetitiveBoard.cpp
	g++ $(ver) -c CompetitiveBoard.cpp -g

AIcomputationD.o: AIcomputation.cpp
	g++ $(ver) -c AIcomputation.cpp -g

AIalienD.o: AIalien.cpp
	g++ $(ver) -c AIalien.cpp -g

AIMissileD.o: AIMissile.cpp
	g++ $(ver) -c AIMissile.cpp -g

AIPlayerD.o: AIPlayer.cpp
	g++ $(ver) -c AIPlayer.cpp -g

AIUpdateD.o: AIUpdate.cpp
	g++ $(ver) -c AIUpdate.cpp -g

AID.o: AI.cpp
	g++ $(ver) -c AI.cpp -g

udpD.o: udp.cpp
	g++ $(ver) -c udp.cpp -g

ImageD.o: Image.cpp
	g++ $(ver) -c Image.cpp -g

HighscoreD.o: Highscore.cpp
	g++ $(ver) -c Highscore.cpp -g

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
	rm -rf Test Game CompGame  Debug.txt
