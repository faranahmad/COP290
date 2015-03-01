QTINC = -c -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I. -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I. -I.

all: UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp ClientCombined.cpp main.o login.o newusersignup.o fileaccess.o file.o share.o connecting.o filesonserver.o sharedwithothers.o moc_login.o moc_newusersignup.o moc_fileaccess.o moc_file.o moc_share.o moc_connecting.o moc_sharedwithothers.o
	g++ -std=c++11 -g -m64 -o welcome UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp ClientCombined.cpp main.o login.o newusersignup.o fileaccess.o file.o share.o connecting.o filesonserver.o sharedwithothers.o moc_login.o moc_newusersignup.o moc_fileaccess.o moc_file.o moc_share.o moc_connecting.o moc_sharedwithothers.o   -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread -lboost_system -lboost_filesystem -lssl -lcrypto

main.o: main.cpp
	g++ $(QTINC) -o main.o main.cpp

file.o: file.cpp
	g++ $(QTINC) -o file.o file.cpp

login.o: login.cpp
	g++ $(QTINC) -o login.o login.cpp

fileaccess.o: fileaccess.cpp
	g++ $(QTINC) -o fileaccess.o fileaccess.cpp

share.o: share.cpp
	g++ $(QTINC) -o share.o share.cpp

newusersignup.o: newusersignup.cpp
	g++ $(QTINC) -o newusersignup.o newusersignup.cpp

connecting.o: connecting.cpp
	g++ $(QTINC) -o connecting.o connecting.cpp

filesonserver.o: filesonserver.cpp
	g++ $(QTINC) -o filesonserver.o filesonserver.cpp

sharedwithothers.o: sharedwithothers.cpp
	g++ $(QTINC) -o sharedwithothers.o sharedwithothers.cpp

moc_login.o: moc_login.cpp
	g++ $(QTINC) -o moc_login.o moc_login.cpp

moc_newusersignup.o: moc_newusersignup.cpp
	g++ $(QTINC) -o moc_newusersignup.o moc_newusersignup.cpp

moc_fileaccess.o: moc_fileaccess.cpp
	g++ $(QTINC) -o moc_fileaccess.o moc_fileaccess.cpp

moc_file.o: moc_file.cpp
	g++ $(QTINC) -o moc_file.o moc_file.cpp

moc_share.o: moc_share.cpp
	g++ $(QTINC) -o moc_share.o moc_share.cpp

moc_connecting.o: moc_connecting.cpp
	g++ $(QTINC) -o moc_connecting.o moc_connecting.cpp

moc_sharedwithothers.o: moc_sharedwithothers.cpp
	g++ $(QTINC) -o moc_sharedwithothers.o moc_sharedwithothers.cpp

clean:
	rm -rf *.o
	rm -rf welcome
