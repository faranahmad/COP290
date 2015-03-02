objtest = object/Test/
objclient = object/Client/
objserver = object/Server/
doxycl= Document/client_latex/
doxyse= Document/server_latex/
design= Document/design_doc/
doc = Document/

qtincnormal = -c -m64 -pipe -std=c++0x -fPIE  -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I. -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I. -I.

qtincluding  = -c -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I../server -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I. -I. -I.

srctest = src/Test/
srcclient = src/Client/
srcserver = src/Server/

exectest = exec/Test/
execclient = exec/Client/
execserver = exec/Server/
execdebugcl = exec/Debug/Client/
execdebugse = exec/Debug/Server/

all: $(exectest)Test $(execclient)Client $(execserver)server

DEBUG: $(execdebugcl)Client 

Document: $(doc)DesignDoc.pdf $(doc)client.pdf $(doc)server.pdf

$(doc)DesignDoc.pdf:
	cd $(design) ; make
	mv $(design)DesignDoc.pdf $(doc)DesignDoc.pdf

$(doc)client.pdf:
	cd $(doxycl) ; make
	mv $(doxycl)refman.pdf $(doc)client.pdf

$(doc)server.pdf:
	cd $(doxyse) ; make
	mv $(doxyse)refman.pdf $(doc)server.pdf

$(exectest)Test: $(objtest)Test.o $(objtest)AllTests.o $(objtest)User.o $(objtest)UserBase.o $(objtest)UserTests.o $(objtest)UserBaseTests.o
	g++ -std=c++11 -o $(exectest)Test $(objtest)Test.o $(objtest)AllTests.o $(objtest)User.o $(objtest)UserBase.o $(objtest)UserTests.o $(objtest)UserBaseTests.o

$(objtest)Test.o: $(srctest)Test.cpp
	g++ -std=c++11 -c -o $(objtest)Test.o $(srctest)Test.cpp

$(objtest)AllTests.o: $(srctest)AllTests.cpp
	g++ -std=c++11 -c -o $(objtest)AllTests.o $(srctest)AllTests.cpp

$(objtest)User.o: $(srctest)User.cpp
	g++ -std=c++11 -c -o $(objtest)User.o $(srctest)User.cpp

$(objtest)UserBase.o: $(srctest)UserBase.cpp
	g++ -std=c++11 -c -o $(objtest)UserBase.o $(srctest)UserBase.cpp

$(objtest)UserTests.o: $(srctest)UserTests.cpp
	g++ -std=c++11 -c -o $(objtest)UserTests.o $(srctest)UserTests.cpp

$(objtest)UserBaseTests.o: $(srctest)UserBaseTests.cpp
	g++ -std=c++11 -c -o $(objtest)UserBaseTests.o $(srctest)UserBaseTests.cpp

RunTest: $(exectest)Test
	cd $(exectest) ; ./Test

clientdebug: $(execdebugcl)Client
	cd $(execdebugcl); ./Client $(ip) $(port)

client: $(execclient)Client
	cd $(execclient); ./Client $(ip) $(port)

server: $(execserver)server
	cd $(execserver) ; sudo ./server $(ip) $(port)

$(execdebugcl)Client: $(srcclient)UserFiles.cpp $(srcclient)FileHistory.cpp $(srcclient)FileChanges.cpp $(srcclient)FileSharing.cpp $(srcclient)FileReceiving.cpp $(srcclient)SyncManager.cpp $(srcclient)ClientCombined.cpp $(objclient)main.o $(objclient)login.o $(objclient)newusersignup.o $(objclient)fileaccess.o $(objclient)file.o $(objclient)share.o $(objclient)connecting.o $(objclient)filesonserver.o $(objclient)sharedwithothers.o $(objclient)moc_login.o $(objclient)moc_newusersignup.o $(objclient)moc_fileaccess.o $(objclient)moc_file.o $(objclient)moc_share.o $(objclient)moc_connecting.o $(objclient)moc_sharedwithothers.o
	g++ -DDEBUG -std=c++11 -m64 -o $(execdebugcl)Client $(srcclient)UserFiles.cpp $(srcclient)FileHistory.cpp $(srcclient)FileChanges.cpp $(srcclient)FileSharing.cpp $(srcclient)FileReceiving.cpp $(srcclient)SyncManager.cpp $(srcclient)ClientCombined.cpp $(objclient)main.o $(objclient)login.o $(objclient)newusersignup.o $(objclient)fileaccess.o $(objclient)file.o $(objclient)share.o $(objclient)connecting.o $(objclient)filesonserver.o $(objclient)sharedwithothers.o $(objclient)moc_login.o $(objclient)moc_newusersignup.o $(objclient)moc_fileaccess.o $(objclient)moc_file.o $(objclient)moc_share.o $(objclient)moc_connecting.o $(objclient)moc_sharedwithothers.o   -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread -lboost_system -lboost_filesystem -lssl -lcrypto

$(execclient)Client: $(objclient)UserFiles.o $(objclient)FileHistory.o $(objclient)FileChanges.o $(objclient)FileSharing.o $(objclient)FileReceiving.o $(objclient)SyncManager.o $(objclient)ClientCombined.o $(objclient)main.o $(objclient)login.o $(objclient)newusersignup.o $(objclient)fileaccess.o $(objclient)file.o $(objclient)share.o $(objclient)connecting.o $(objclient)filesonserver.o $(objclient)sharedwithothers.o $(objclient)moc_login.o $(objclient)moc_newusersignup.o $(objclient)moc_fileaccess.o $(objclient)moc_file.o $(objclient)moc_share.o $(objclient)moc_connecting.o $(objclient)moc_sharedwithothers.o  	
	g++ -std=c++11 -m64 -o $(execclient)Client $(objclient)UserFiles.o $(objclient)FileHistory.o $(objclient)FileChanges.o $(objclient)FileSharing.o $(objclient)FileReceiving.o $(objclient)SyncManager.o $(objclient)ClientCombined.o $(objclient)main.o $(objclient)login.o $(objclient)newusersignup.o $(objclient)fileaccess.o $(objclient)file.o $(objclient)share.o $(objclient)connecting.o $(objclient)filesonserver.o $(objclient)sharedwithothers.o $(objclient)moc_login.o $(objclient)moc_newusersignup.o $(objclient)moc_fileaccess.o $(objclient)moc_file.o $(objclient)moc_share.o $(objclient)moc_connecting.o $(objclient)moc_sharedwithothers.o   -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread -lboost_system -lboost_filesystem -lssl -lcrypto

$(objclient)UserFiles.o: $(srcclient)UserFiles.cpp
	g++ -std=c++11 -c -o $(objclient)UserFiles.o $(srcclient)UserFiles.cpp

$(objclient)FileHistory.o: $(srcclient)FileHistory.cpp
	g++ -std=c++11 -c -o $(objclient)FileHistory.o $(srcclient)FileHistory.cpp

$(objclient)FileChanges.o: $(srcclient)FileChanges.cpp
	g++ -std=c++11 -c -o $(objclient)FileChanges.o $(srcclient)FileChanges.cpp

$(objclient)FileSharing.o: $(srcclient)FileSharing.cpp
	g++ -std=c++11 -c -o $(objclient)FileSharing.o $(srcclient)FileSharing.cpp

$(objclient)FileReceiving.o: $(srcclient)FileReceiving.cpp
	g++ -std=c++11 -c -o $(objclient)FileReceiving.o $(srcclient)FileReceiving.cpp

$(objclient)SyncManager.o: $(srcclient)SyncManager.cpp
	g++ -std=c++11 -c -o $(objclient)SyncManager.o $(srcclient)SyncManager.cpp

$(objclient)ClientCombined.o: $(srcclient)ClientCombined.cpp 
	g++ -std=c++11 -c -o $(objclient)ClientCombined.o $(srcclient)ClientCombined.cpp

$(objclient)main.o: $(srcclient)main.cpp
	g++ $(qtincnormal) -o $(objclient)main.o $(srcclient)main.cpp 

$(objclient)login.o: $(srcclient)login.cpp
	g++ $(qtincnormal) -o $(objclient)login.o $(srcclient)login.cpp

$(objclient)newusersignup.o: $(srcclient)newusersignup.cpp
	g++ $(qtincnormal) -o $(objclient)newusersignup.o $(srcclient)newusersignup.cpp

$(objclient)fileaccess.o: $(srcclient)fileaccess.cpp
	g++ $(qtincnormal) -o $(objclient)fileaccess.o $(srcclient)fileaccess.cpp

$(objclient)file.o: $(srcclient)file.cpp
	g++ $(qtincnormal) -o $(objclient)file.o $(srcclient)file.cpp

$(objclient)share.o: $(srcclient)share.cpp
	g++ $(qtincnormal) -o $(objclient)share.o $(srcclient)share.cpp

$(objclient)connecting.o: $(srcclient)connecting.cpp
	g++ $(qtincnormal) -o $(objclient)connecting.o $(srcclient)connecting.cpp

$(objclient)filesonserver.o: $(srcclient)filesonserver.cpp
	g++ $(qtincnormal) -o $(objclient)filesonserver.o $(srcclient)filesonserver.cpp

$(objclient)sharedwithothers.o: $(srcclient)sharedwithothers.cpp
	g++ $(qtincnormal) -o $(objclient)sharedwithothers.o $(srcclient)sharedwithothers.cpp

$(objclient)moc_login.o: $(srcclient)moc_login.cpp
	g++ $(qtincnormal) -o $(objclient)moc_login.o $(srcclient)moc_login.cpp 

$(objclient)moc_newusersignup.o: $(srcclient)moc_newusersignup.cpp
	g++ $(qtincnormal) -o $(objclient)moc_newusersignup.o $(srcclient)moc_newusersignup.cpp

$(objclient)moc_fileaccess.o: $(srcclient)moc_fileaccess.cpp
	g++ $(qtincnormal) -o $(objclient)moc_fileaccess.o $(srcclient)moc_fileaccess.cpp 

$(objclient)moc_file.o: $(srcclient)moc_file.cpp
	g++ $(qtincnormal) -o $(objclient)moc_file.o $(srcclient)moc_file.cpp

$(objclient)moc_share.o: $(srcclient)moc_share.cpp 
	g++ $(qtincnormal) -o $(objclient)moc_share.o $(srcclient)moc_share.cpp

$(objclient)moc_connecting.o: $(srcclient)moc_connecting.cpp
	g++ $(qtincnormal) -o $(objclient)moc_connecting.o $(srcclient)moc_connecting.cpp

$(objclient)moc_sharedwithothers.o: $(srcclient)moc_sharedwithothers.cpp
	g++ $(qtincnormal) -o $(objclient)moc_sharedwithothers.o $(srcclient)moc_sharedwithothers.cpp

$(execserver)server: $(objserver)User.o $(objserver)UserBase.o $(objserver)FileHistory.o $(objserver)Server2.o  $(objserver)main.o $(objserver)server.o $(objserver)onlineusers.o $(objserver)allusers.o $(objserver)serverfilesandfolders.o $(objserver)moc_server.o $(objserver)moc_onlineusers.o $(objserver)moc_allusers.o $(objserver)moc_serverfilesandfolders.o
	g++ -m64 -std=c++11 -o $(execserver)server $(objserver)User.o $(objserver)UserBase.o $(objserver)FileHistory.o $(objserver)Server2.o  $(objserver)main.o $(objserver)server.o $(objserver)onlineusers.o $(objserver)allusers.o $(objserver)serverfilesandfolders.o $(objserver)moc_server.o $(objserver)moc_onlineusers.o $(objserver)moc_allusers.o $(objserver)moc_serverfilesandfolders.o -L/usr/X11R6/lib64 -lQt5Widgets -L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lGL -lpthread -lboost_filesystem -lboost_system -lssl -lcrypto -lpthread

$(objserver)User.o: $(srcserver)User.cpp
	g++ -std=c++11 -c -o $(objserver)User.o $(srcserver)User.cpp

$(objserver)UserBase.o: $(srcserver)UserBase.cpp
	g++ -std=c++11 -c -o $(objserver)UserBase.o $(srcserver)UserBase.cpp

$(objserver)FileHistory.o: $(srcserver)FileHistory.cpp
	g++ -std=c++11 -c -o $(objserver)FileHistory.o $(srcserver)FileHistory.cpp

$(objserver)Server2.o: $(srcserver)Server2.cpp
	g++ -std=c++11 -c -o $(objserver)Server2.o $(srcserver)Server2.cpp

$(objserver)main.o: $(srcserver)main.cpp
	g++ $(qtincluding) -o $(objserver)main.o $(srcserver)main.cpp

$(objserver)server.o: $(srcserver)server.cpp
	g++ $(qtincluding) -o $(objserver)server.o $(srcserver)server.cpp

$(objserver)onlineusers.o: $(srcserver)onlineusers.cpp
	g++ $(qtincluding) -o $(objserver)onlineusers.o $(srcserver)onlineusers.cpp

$(objserver)allusers.o: $(srcserver)allusers.cpp
	g++ $(qtincluding) -o $(objserver)allusers.o $(srcserver)allusers.cpp

$(objserver)serverfilesandfolders.o: $(srcserver)serverfilesandfolders.cpp
	g++ $(qtincluding) -o $(objserver)serverfilesandfolders.o $(srcserver)serverfilesandfolders.cpp

$(objserver)moc_server.o: $(srcserver)moc_server.cpp
	g++ $(qtincluding) -o $(objserver)moc_server.o $(srcserver)moc_server.cpp

$(objserver)moc_onlineusers.o: $(srcserver)moc_onlineusers.cpp
	g++ $(qtincluding) -o $(objserver)moc_onlineusers.o $(srcserver)moc_onlineusers.cpp

$(objserver)moc_allusers.o: $(srcserver)moc_allusers.cpp
	g++ $(qtincluding) -o $(objserver)moc_allusers.o $(srcserver)moc_allusers.cpp

$(objserver)moc_serverfilesandfolders.o: $(srcserver)moc_serverfilesandfolders.cpp
	g++ $(qtincluding) -o $(objserver)moc_serverfilesandfolders.o $(srcserver)moc_serverfilesandfolders.cpp


clean:
	cd $(objtest) ; rm -rf *.o
	cd $(objclient) ; rm -rf *.o
	cd $(objserver) ; rm -rf *.o
	cd $(exectest) ; rm -rf Test
	cd $(execclient) ; rm -rf Client
	cd $(execdebugcl) ; rm -rf Client
	cd $(execserver) ; rm -rf server
	cd $(doc) ; rm -rf *.pdf
	cd $(design) ; make clean
	cd $(doxyse) ; make clean
	cd $(doxycl) ; make clean
