Compiler= g++
Debugger= gdb
Arguments= -std=c++11 
Mode= -c
IncludeThread= -lpthread
IncludeGraphics= -lGL -lGLU -lglut
FolderObj= Object_Files/
FolderExec= Executibles/
Folder3d = SRC/3D/
FolderCommon =SRC/Common/
FolderInter2D= SRC/InterThread/
FolderIndterMN2d=SRC/InterThreadMN/
DebugDefine= -DDEBUG 

all: 3D 2D 2DMN

printDebug: 3DPrintDebug 2DPrintDebug 2DMNPrintDebug

3D: Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o
	$(Compiler) $(Arguments) -o 3D $(FolderObj)Color.o $(FolderObj)3DBall.o $(FolderObj)3DBoard.o $(FolderObj)Image.o $(FolderObj)3DThreads.o $(IncludeThread) $(IncludeGraphics) 
	mv 3D $(FolderExec)3D
3DPrintDebug:ColorPrintDebug.o 3DBallPrintDebug.o 3DBoardPrintDebug.o ImagePrintDebug.o 3DThreadsPrintDebug.o
	$(Compiler) $(DebugDefine) $(Arguments) -o 3DPrintDebug $(FolderObj)ColorPrintDebug.o $(FolderObj)3DBallPrintDebug.o $(FolderObj)3DBoardPrintDebug.o $(FolderObj)ImagePrintDebug.o $(FolderObj)3DThreadsPrintDebug.o $(IncludeThread) $(IncludeGraphics) $(DebugDefine)
	mv 3DPrintDebug $(FolderExec)3DPrintDebug
	
Color.o: $(FolderCommon)Color.cpp
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp 
	mv Color.o $(FolderObj)Color.o
ColorPrintDebug.o: $(FolderCommon)Color.cpp
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp 
	mv Color.o $(FolderObj)ColorPrintDebug.o

3DBall.o: Color.o $(Folder3d)3DBall.cpp 
	$(Compiler) $(Mode) $(Arguments)  $(FolderObj)Color.o $(Folder3d)3DBall.cpp 
	mv 3DBall.o $(FolderObj)3DBall.o
3DBallPrintDebug.o: Color.o $(Folder3d)3DBall.cpp 
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments)  $(FolderObj)Color.o $(Folder3d)3DBall.cpp 
	mv 3DBall.o $(FolderObj)3DBallPrintDebug.o

3DBoard.o: 3DBall.o $(Folder3d)3DBoard.cpp 
	$(Compiler) $(Mode) $(Arguments)  $(FolderObj)Color.o $(FolderObj)3DBall.o  $(Folder3d)3DBoard.cpp 
	mv 3DBoard.o $(FolderObj)3DBoard.o
3DBoardPrintDebug.o: 3DBall.o $(Folder3d)3DBoard.cpp 
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments)  $(FolderObj)Color.o $(FolderObj)3DBall.o  $(Folder3d)3DBoard.cpp 
	mv 3DBoard.o $(FolderObj)3DBoardPrintDebug.o

Image.o: $(FolderCommon)Image.cpp
	$(Compiler) $(Mode) $(Arguments) $(IncludingGraphics) $(FolderCommon)Image.cpp
	mv Image.o $(FolderObj)Image.o
ImagePrintDebug.o: $(FolderCommon)Image.cpp
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments) $(IncludingGraphics) $(FolderCommon)Image.cpp
	mv Image.o $(FolderObj)ImagePrintDebug.o

3DThreads.o: Image.o Color.o 3DBall.o 3DBoard.o $(Folder3d)3DThreads.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderObj)Image.o $(FolderObj)Color.o $(FolderObj)3DBall.o $(FolderObj)3DBoard.o $(Folder3d)3DThreads.cpp
	mv 3DThreads.o $(FolderObj)3DThreads.o
3DThreadsPrintDebug.o: Image.o Color.o 3DBall.o 3DBoard.o $(Folder3d)3DThreads.cpp
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderObj)Image.o $(FolderObj)Color.o $(FolderObj)3DBall.o $(FolderObj)3DBoard.o $(Folder3d)3DThreads.cpp
	mv 3DThreads.o $(FolderObj)3DThreadsPrintDebug.o

Ball.o: $(FolderCommon)Ball.cpp Color.o
	$(Compiler) $(Mode) $(Arguments)  $(FolderObj)Color.o $(FolderCommon)Ball.cpp 
	mv Ball.o $(FolderObj)Ball.o
BallPrintDebug.o: $(FolderCommon)Ball.cpp Color.o
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments)  $(FolderObj)Color.o $(FolderCommon)Ball.cpp 
	mv Ball.o $(FolderObj)BallPrintDebug.o

Board.o: Ball.o $(FolderCommon)Board.cpp 
	$(Compiler) $(Mode) $(Arguments)  $(FolderObj)Color.o $(FolderObj)Ball.o  $(FolderCommon)Board.cpp 
	mv Board.o $(FolderObj)Board.o
BoardPrintDebug.o: Ball.o $(FolderCommon)Board.cpp 
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments)  $(FolderObj)Color.o $(FolderObj)Ball.o  $(FolderCommon)Board.cpp 
	mv Board.o $(FolderObj)BoardPrintDebug.o

Message.o: $(FolderCommon)Message.cpp
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Message.cpp
	mv Message.o $(FolderObj)Message.o
MessagePrintDebug.o: $(FolderCommon)Message.cpp
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments)  $(FolderCommon)Message.cpp
	mv Message.o $(FolderObj)MessagePrintDebug.o

2DThreads.o: Image.o Color.o Ball.o Board.o Message.o  $(FolderInter2D)Threads.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderObj)Image.o $(FolderObj)Color.o $(FolderObj)Ball.o $(FolderObj)Board.o  $(FolderObj)Message.o $(FolderInter2D)Threads.cpp
	mv Threads.o $(FolderObj)2DThreads.o
2DThreadsPrintDebug.o: Image.o Color.o Ball.o Board.o Message.o  $(FolderInter2D)Threads.cpp
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderObj)Image.o $(FolderObj)Color.o $(FolderObj)Ball.o $(FolderObj)Board.o  $(FolderObj)Message.o $(FolderInter2D)Threads.cpp
	mv Threads.o $(FolderObj)2DThreadsPrintDebug.o

2DThreadsMN.o: Image.o Color.o Ball.o Board.o Message.o $(FolderIndterMN2d)Threads.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderObj)Image.o $(FolderObj)Color.o $(FolderObj)Ball.o $(FolderObj)Board.o  $(FolderObj)Message.o $(FolderIndterMN2d)Threads.cpp
	mv Threads.o $(FolderObj)2DThreadsMN.o
2DThreadsMNPrintDebug.o: Image.o Color.o Ball.o Board.o Message.o $(FolderIndterMN2d)Threads.cpp
	$(Compiler) $(DebugDefine) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderObj)Image.o $(FolderObj)Color.o $(FolderObj)Ball.o $(FolderObj)Board.o  $(FolderObj)Message.o $(FolderIndterMN2d)Threads.cpp
	mv Threads.o $(FolderObj)2DThreadsMNPrintDebug.o

2D: Image.o Color.o Ball.o Board.o Message.o 2DThreads.o
	$(Compiler) $(Arguments) -o 2D $(FolderObj)Color.o $(FolderObj)Ball.o $(FolderObj)Board.o $(FolderObj)Image.o  $(FolderObj)Message.o $(FolderObj)2DThreads.o $(IncludeThread) $(IncludeGraphics) 
	mv 2D $(FolderExec)2D
2DPrintDebug: ImagePrintDebug.o ColorPrintDebug.o BallPrintDebug.o BoardPrintDebug.o MessagePrintDebug.o 2DThreadsPrintDebug.o
	$(Compiler) $(DebugDefine) $(Arguments) -o 2DPrintDebug $(FolderObj)ColorPrintDebug.o $(FolderObj)BallPrintDebug.o $(FolderObj)BoardPrintDebug.o $(FolderObj)ImagePrintDebug.o  $(FolderObj)MessagePrintDebug.o $(FolderObj)2DThreadsPrintDebug.o $(IncludeThread) $(IncludeGraphics)
	mv 2DPrintDebug $(FolderExec)2DPrintDebug

2DMN: Image.o Color.o Ball.o Board.o Message.o 2DThreadsMN.o
	$(Compiler) $(Arguments) -o 2DMN $(FolderObj)Color.o $(FolderObj)Ball.o $(FolderObj)Board.o $(FolderObj)Image.o  $(FolderObj)Message.o $(FolderObj)2DThreadsMN.o $(IncludeThread) $(IncludeGraphics) 
	mv 2DMN $(FolderExec)2DMN
2DMNPrintDebug: ImagePrintDebug.o ColorPrintDebug.o BallPrintDebug.o BoardPrintDebug.o MessagePrintDebug.o 2DThreadsMNPrintDebug.o
	$(Compiler) $(DebugDefine) $(Arguments) -o 2DMNPrintDebug $(FolderObj)ColorPrintDebug.o $(FolderObj)BallPrintDebug.o $(FolderObj)BoardPrintDebug.o $(FolderObj)ImagePrintDebug.o  $(FolderObj)MessagePrintDebug.o $(FolderObj)2DThreadsMNPrintDebug.o $(IncludeThread) $(IncludeGraphics)
	mv 2DMNPrintDebug $(FolderExec)2DMNPrintDebug


Run3D: 3D
	cd $(FolderExec) ; ./3D $(num_thread)  
Run3DPrintDebug: 3DPrintDebug
	cd $(FolderExec) ; ./3DPrintDebug $(num_thread)  

Run2D: 2D
	cd $(FolderExec) ; ./2D $(num_thread)
Run2DPrintDebug: 2DPrintDebug
	cd $(FolderExec) ; ./2DPrintDebug $(num_thread)

Run2DMN: 2DMN
	cd $(FolderExec) ; ./2DMN $(m) $(n)
Run2DMNPrintDebug: 2DMNPrintDebug
	cd $(FolderExec) ; ./2DMNPrintDebug $(m) $(n)

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 
	rm a.out 
	
clean:
	rm -rf $(FolderObj)*.o 3D
	rm -rf $(FolderObj)*.o
	rm -rf $(FolderExec)3D
	rm -rf $(FolderExec)2D
	rm -rf $(FolderExec)2DMN
	rm -rf $(FolderExec)a.out