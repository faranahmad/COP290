QTINC=-c -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I. -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I. -I.

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

Manager: SyncManager.cpp FileChanges.cpp UserFiles.cpp FileHistory.cpp FileSharing.cpp FileReceiving.cpp
	g++ -std=c++11 UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp -lboost_system -lboost_filesystem -lssl -lcrypto -lpthread
	./a.out

Client:SyncManager.cpp FileChanges.cpp UserFiles.cpp FileHistory.cpp FileSharing.cpp FileReceiving.cpp ClientCombined.cpp
	g++ -std=c++11 UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp ClientCombined.cpp -lboost_system -lboost_filesystem -lssl -lcrypto -lpthread
	# ./a.out

main.o: main.cpp
	g++ $(QTINC) -o main.o main.cpp
	
fileaccess.o: fileaccess.cpp
	g++ $(QTINC) -o fileaccess.o fileaccess.cpp

share.o:
	g++ $(QTINC) -o share.o share.cpp

newusersignup.o:
	g++ $(QTINC) -o newusersignup.o newusersignup.cpp

file.o:
	g++ $(QTINC) -o file.o file.cpp

connecting.o:
	g++ $(QTINC) -o connecting.o connecting.cpp

filesonserver.o: filesonserver.cpp
	g++ $(QTINC) -o filesonserver.o filesonserver.cpp

moc_login.o:moc_login.cpp
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

login.o: login.cpp
	g++ $(QTINC) -o login.o login.cpp

QTUI: UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp ClientCombined.cpp main.o login.o newusersignup.o fileaccess.o file.o share.o connecting.o filesonserver.o moc_login.o moc_newusersignup.o moc_fileaccess.o moc_file.o moc_share.o moc_connecting.o 
	g++ -std=c++11 -m64 -o welcome UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp ClientCombined.cpp main.o login.o newusersignup.o fileaccess.o file.o share.o connecting.o filesonserver.o moc_login.o moc_newusersignup.o moc_fileaccess.o moc_file.o moc_share.o moc_connecting.o   -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread -lboost_system -lboost_filesystem -lssl -lcrypto

	# g++ -std=c++11 -c  UserFiles.cpp FileHistory.cpp FileChanges.cpp FileSharing.cpp FileReceiving.cpp SyncManager.cpp ClientCombined.cpp -lboost_system -lboost_filesystem -lssl -lcrypto -lpthread
	# g++ -std=c++11 -m64 -o client  ClientCombined.o main.o login.o newusersignup.o fileaccess.o moc_login.o moc_newusersignup.o moc_fileaccess.o  -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread
	

	# ./welcome

clean:
	rm -rf a.out
	rm -rf *.o
	rm -rf welcome
	# rm -rf Instruction.txt
