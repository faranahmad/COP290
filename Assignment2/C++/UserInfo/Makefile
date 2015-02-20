test: User.cpp Test.cpp UserTests.cpp AllTests.cpp
	g++ -std=c++11 User.cpp Test.cpp UserTests.cpp AllTests.cpp
	./a.out

history: FileHistory.cpp
	g++ -std=c++11 FileHistory.cpp -lboost_filesystem -lboost_system 
	./a.out

changes: FileHistory.cpp FileChanges.cpp UserFiles.cpp
	g++ -std=c++11 UserFiles.cpp FileHistory.cpp FileChanges.cpp -lboost_filesystem -lboost_system 
	./a.out

Files:UserFiles.cpp
	g++ -std=c++11 UserFiles.cpp
	./a.out

Run: User.cpp UserBase.cpp
	g++ -std=c++11 User.cpp UserBase.cpp
	./a.out
client: User.cpp UserBase.cpp Client.cpp
	g++ -std=c++11 User.cpp UserBase.cpp Client.cpp
	./a.out

server: User.cpp UserBase.cpp tcpserver.cpp
	g++ -std=c++11 User.cpp UserBase.cpp tcpserver.cpp
	./a.out

clean:
	rm -rf a.out
	rm -rf Instruction.txt
