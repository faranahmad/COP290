QTTHINGS=g++ -c -m64 -pipe -g -Wall -W -D_REENTRANT -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I../welcome -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I. -I. -I.
all:
	$(QTTHINGS) -o main.o main.cpp
	$(QTTHINGS) -o login.o login.cpp
	$(QTTHINGS) -o newusersignup.o newusersignup.cpp
	$(QTTHINGS) -o fileaccess.o fileaccess.cpp
	$(QTTHINGS) -o moc_login.o moc_login.cpp
	$(QTTHINGS) -o moc_newusersignup.o moc_newusersignup.cpp
	$(QTTHINGS) -o moc_fileaccess.o moc_fileaccess.cpp
	g++ -m64 -o welcome main.o login.o newusersignup.o fileaccess.o moc_login.o moc_newusersignup.o moc_fileaccess.o   -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread
	./welcome


client: User.cpp UserBase.cpp Client.cpp
	$(QTTHINGS) -o main.o main.cpp
	$(QTTHINGS) -o login.o login.cpp
	$(QTTHINGS) -o newusersignup.o newusersignup.cpp
	$(QTTHINGS) -o fileaccess.o fileaccess.cpp
	$(QTTHINGS) -o moc_login.o moc_login.cpp
	$(QTTHINGS) -o moc_newusersignup.o moc_newusersignup.cpp
	$(QTTHINGS) -o moc_fileaccess.o moc_fileaccess.cpp
	g++ -std=c++11 -c -o Client.o Client.cpp
	g++ -std=c++11 -m64 -o client  Client.o main.o login.o newusersignup.o fileaccess.o moc_login.o moc_newusersignup.o moc_fileaccess.o  -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread
	# g++ -std=c++11 -o client User.cpp UserBase.cpp Client.cpp
	./client

server: User.cpp UserBase.cpp tcpserver.cpp
	g++ -std=c++11 -o server User.cpp UserBase.cpp tcpserver.cpp
	./server

clean:
	rm -rf *.o
	rm -rf client
	rm -rf server
	rm -rf welcome