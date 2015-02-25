xyz = -c -m64 -pipe -g -D_REENTRANT -Wall -W -fPIE -DQT_GUI_LIB -DQT_CORE_LIB -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I../cpp -I/usr/include/qt5 -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -Idebug -I.

all:
	g++ $(xyz) -o diff_match_patch.o diff_match_patch.cpp
	g++ $(xyz) -o diff_match_patch_test.o diff_match_patch_test.cpp
	g++ -m64 -o diff_match_patch diff_match_patch.o diff_match_patch_test.o   -L/usr/X11R6/lib64 -lQt5Gui -L/usr/lib/x86_64-linux-gnu -lQt5Core -lGL -lpthread 
