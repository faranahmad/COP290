qtincluding  = -c -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I../server -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I. -I. -I.

server: User.cpp UserBase.cpp FileHistory.cpp Server2.cpp main.o server.o onlineusers.o allusers.o serverfilesandfolders.o moc_server.o moc_onlineusers.o moc_allusers.o moc_serverfilesandfolders.o
	g++ -m64 -std=c++11 -o server User.cpp UserBase.cpp FileHistory.cpp Server2.cpp main.o server.o onlineusers.o allusers.o serverfilesandfolders.o moc_server.o moc_onlineusers.o moc_allusers.o moc_serverfilesandfolders.o   -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread -lboost_filesystem -lboost_system -lssl -lcrypto -lpthread

main.o: main.cpp
	g++ $(qtincluding) -o main.o main.cpp

server.o: server.cpp
	g++ $(qtincluding) -o server.o server.cpp

onlineusers.o: onlineusers.cpp
	g++ $(qtincluding) -o onlineusers.o onlineusers.cpp

allusers.o: allusers.cpp
	g++ $(qtincluding) -o allusers.o allusers.cpp

serverfilesandfolders.o: serverfilesandfolders.cpp
	g++ $(qtincluding) -o serverfilesandfolders.o serverfilesandfolders.cpp

moc_server.o: moc_server.cpp
	g++ $(qtincluding) -o moc_server.o moc_server.cpp

moc_onlineusers.o: moc_onlineusers.cpp
	g++ $(qtincluding) -o moc_onlineusers.o moc_onlineusers.cpp

moc_allusers.o: moc_allusers.cpp
	g++ $(qtincluding) -o moc_allusers.o moc_allusers.cpp

moc_serverfilesandfolders.o: moc_serverfilesandfolders.cpp
	g++ $(qtincluding) -o moc_serverfilesandfolders.o moc_serverfilesandfolders.cpp

all: server

clean:
	rm -rf *.o
	rm -rf server
