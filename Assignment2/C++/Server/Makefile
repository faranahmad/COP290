test: User.cpp Test.cpp UserTests.cpp AllTests.cpp
	g++ -std=c++11 User.cpp Test.cpp UserTests.cpp AllTests.cpp
	./a.out

Run: User.cpp UserBase.cpp
	g++ -std=c++11 User.cpp UserBase.cpp
	./a.out
client: User.cpp UserBase.cpp Client.cpp
	g++ -std=c++11 User.cpp UserBase.cpp Client.cpp -o Client -lboost_filesystem -lboost_system -lssl -lcrypto -lpthread

server: User.cpp UserBase.cpp FileHistory.cpp Server.cpp
	g++ -std=c++11 User.cpp UserBase.cpp FileHistory.cpp Server.cpp -o Server -lboost_filesystem -lboost_system -lssl -lcrypto -lpthread

clean:
	rm -rf a.out
