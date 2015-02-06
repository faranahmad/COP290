test: User.cpp Test.cpp UserTests.cpp AllTests.cpp
	g++ -std=c++11 User.cpp Test.cpp UserTests.cpp AllTests.cpp
	./a.out

Run: User.cpp UserBase.cpp
	g++ -std=c++11 User.cpp UserBase.cpp
	./a.out
client: User.cpp UserBase.cpp Client.cpp
	g++ -std=c++11 User.cpp UserBase.cpp Client.cpp
	./a.out

server: User.cpp UserBase.cpp Server.cpp
	g++ -std=c++11 User.cpp UserBase.cpp Server.cpp -o Server

clean:
	rm -rf a.out
