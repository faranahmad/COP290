ver = -std=c++11

SRC=SRC/
OBJ= Object/
EXE=Exec/
DOC=Document/DesignDoc
DOXY=Document/DoxygenLatex
Pres=Document/Presentation


all: $(EXE)Game $(EXE)CompGame 

Debug: $(EXE)GameDebug

RunGame: $(EXE)Game
	cd $(EXE); ./Game $(ip) $(name)

RunCompGame: $(EXE)CompGame
	cd $(EXE); ./CompGame $(ip) $(name)

RunGameDebug: $(EXE)GameDebug
	cd $(EXE) ; gdb ./GameDebug

Documentation: DesignDoc Presentation Doxygen

DesignDoc:
	cd $(DOC); make 

Presentation:
	cd $(Pres); make

Doxygen:
	cd $(DOXY); make

RunTest: Test
	./Test

$(EXE)Game: $(OBJ)Alien.o $(OBJ)Ship.o $(OBJ)Color.o $(OBJ)Bullet.o $(OBJ)Board.o $(OBJ)AIcomputation.o $(OBJ)AIalien.o $(OBJ)AIMissile.o $(OBJ)AIPlayer.o $(OBJ)AIUpdate.o $(OBJ)udp.o $(OBJ)Image.o $(OBJ)Highscore.o $(OBJ)Combined.o
	g++ $(ver) -o $(EXE)Game $(OBJ)Color.o $(OBJ)Ship.o $(OBJ)Bullet.o $(OBJ)Alien.o $(OBJ)Board.o $(OBJ)AIcomputation.o $(OBJ)AIalien.o $(OBJ)AIMissile.o $(OBJ)AIPlayer.o $(OBJ)AIUpdate.o $(OBJ)udp.o $(OBJ)Image.o $(OBJ)Highscore.o $(OBJ)Combined.o -lGL -lGLU -lglut -lpthread

$(EXE)CompGame: $(OBJ)Alien.o $(OBJ)Ship.o $(OBJ)Color.o $(OBJ)Bullet.o $(OBJ)CompetitiveBoard.o $(OBJ)OPAIcomputation.o $(OBJ)OPAIalien.o $(OBJ)OPAIMissile.o $(OBJ)OPAIPlayer.o $(OBJ)OPAIUpdate.o $(OBJ)udp.o $(OBJ)Image.o $(OBJ)CompHighscore.o $(OBJ)CompCombined.o
	g++ $(ver) -o $(EXE)CompGame $(OBJ)Alien.o $(OBJ)Ship.o $(OBJ)Color.o $(OBJ)Bullet.o $(OBJ)CompetitiveBoard.o $(OBJ)OPAIcomputation.o $(OBJ)OPAIalien.o $(OBJ)OPAIMissile.o $(OBJ)OPAIPlayer.o $(OBJ)OPAIUpdate.o $(OBJ)udp.o $(OBJ)Image.o $(OBJ)CompHighscore.o $(OBJ)CompCombined.o -lGL -lGLU -lglut -lpthread

$(OBJ)Color.o: $(SRC)Color.cpp
	g++ $(ver) -c -o $(OBJ)Color.o $(SRC)Color.cpp

$(OBJ)Alien.o: $(SRC)Alien.cpp
	g++ $(ver) -c -o $(OBJ)Alien.o $(SRC)Alien.cpp

$(OBJ)Ship.o: $(SRC)Ship.cpp
	g++ $(ver) -c -o $(OBJ)Ship.o $(SRC)Ship.cpp

$(OBJ)Bullet.o: $(SRC)Bullet.cpp
	g++ $(ver) -c -o $(OBJ)Bullet.o $(SRC)Bullet.cpp

$(OBJ)Board.o: $(SRC)Board.cpp
	g++ $(ver) -c -o $(OBJ)Board.o $(SRC)Board.cpp

$(OBJ)CompetitiveBoard.o: $(SRC)CompetitiveBoard.cpp
	g++ $(ver) -c -o $(OBJ)CompetitiveBoard.o $(SRC)CompetitiveBoard.cpp

$(OBJ)AIcomputation.o: $(SRC)AIcomputation.cpp
	g++ $(ver) -c -o $(OBJ)AIcomputation.o $(SRC)AIcomputation.cpp

$(OBJ)AIalien.o: $(SRC)AIalien.cpp
	g++ $(ver) -c -o $(OBJ)AIalien.o $(SRC)AIalien.cpp

$(OBJ)AIMissile.o: $(SRC)AIMissile.cpp
	g++ $(ver) -c -o $(OBJ)AIMissile.o $(SRC)AIMissile.cpp

$(OBJ)AIPlayer.o: $(SRC)AIPlayer.cpp
	g++ $(ver) -c -o $(OBJ)AIPlayer.o $(SRC)AIPlayer.cpp

$(OBJ)AIUpdate.o: $(SRC)AIUpdate.cpp
	g++ $(ver) -c -o $(OBJ)AIUpdate.o $(SRC)AIUpdate.cpp

$(OBJ)OPAIcomputation.o: $(SRC)OPAIcomputation.cpp
	g++ $(ver) -c -o $(OBJ)OPAIcomputation.o $(SRC)OPAIcomputation.cpp

$(OBJ)OPAIalien.o: $(SRC)OPAIalien.cpp
	g++ $(ver) -c -o $(OBJ)OPAIalien.o $(SRC)OPAIalien.cpp

$(OBJ)OPAIMissile.o: $(SRC)OPAIMissile.cpp
	g++ $(ver) -c -o $(OBJ)OPAIMissile.o $(SRC)OPAIMissile.cpp

$(OBJ)OPAIPlayer.o: $(SRC)OPAIPlayer.cpp
	g++ $(ver) -c -o $(OBJ)OPAIPlayer.o $(SRC)OPAIPlayer.cpp

$(OBJ)OPAIUpdate.o: $(SRC)OPAIUpdate.cpp
	g++ $(ver) -c -o $(OBJ)OPAIUpdate.o $(SRC)OPAIUpdate.cpp

$(OBJ)AI.o: $(SRC)AI.cpp
	g++ $(ver) -c -o $(OBJ)AI.o $(SRC)AI.cpp

$(OBJ)udp.o: $(SRC)udp.cpp
	g++ $(ver) -c -o $(OBJ)udp.o $(SRC)udp.cpp

$(OBJ)Image.o: $(SRC)Image.cpp
	g++ $(ver) -c -o $(OBJ)Image.o $(SRC)Image.cpp

$(OBJ)Highscore.o: $(SRC)Highscore.cpp
	g++ $(ver) -c -o $(OBJ)Highscore.o $(SRC)Highscore.cpp

$(OBJ)CompHighscore.o: $(SRC)CompHighscore.cpp
	g++ $(ver) -c -o $(OBJ)CompHighscore.o $(SRC)CompHighscore.cpp

$(OBJ)Combined.o: $(SRC)Combined.cpp
	g++ $(ver) -c -o $(OBJ)Combined.o $(SRC)Combined.cpp -w

$(OBJ)CompCombined.o: $(SRC)CompCombined.cpp
	g++ $(ver) -c -o $(OBJ)CompCombined.o $(SRC)CompCombined.cpp -w

$(EXE)GameDebug: $(SRC)Alien.cpp $(SRC)Ship.cpp $(SRC)Color.cpp $(SRC)Bullet.cpp $(SRC)Board.cpp $(SRC)AIcomputation.cpp $(SRC)AIalien.cpp $(SRC)AIMissile.cpp $(SRC)AIPlayer.cpp $(SRC)AIUpdate.cpp $(SRC)udp.cpp $(SRC)Image.cpp $(SRC)Highscore.cpp $(SRC)Combined.cpp
	g++ $(ver) -o $(EXE)GameDebug $(SRC)Alien.cpp $(SRC)Ship.cpp $(SRC)Color.cpp $(SRC)Bullet.cpp $(SRC)Board.cpp $(SRC)AIcomputation.cpp $(SRC)AIalien.cpp $(SRC)AIMissile.cpp $(SRC)AIPlayer.cpp $(SRC)AIUpdate.cpp $(SRC)udp.cpp $(SRC)Image.cpp $(SRC)Highscore.cpp $(SRC)Combined.cpp -g -lGL -lGLU -lglut -lpthread

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
	cd $(OBJ);	rm -rf *.o
	cd $(EXE);  rm -rf Test Game CompGame Debug.txt
	cd $(DOXY); make clean
	cd $(DOC) ; make clean
	cd $(Pres) ; make clean 
