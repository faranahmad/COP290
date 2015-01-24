Compiler= g++
Debugger= gdb
Arguments= -std=c++11 
Mode= -c
DebugMode= -g
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

GDBDebug: 3DGDBDebug 2DGDBDebug 2DMNGDBDebug

doc:Doc/Design\ Document.tex
	pdflatex Doc/Design\ Document.tex

3D: Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o
	$(Compiler) $(Arguments) -o 3D Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o $(IncludeThread) $(IncludeGraphics) 
	mv 3D $(FolderExec)3D.out
3DPrintDebug:Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o
	$(Compiler) $(DebugDefine) $(Arguments) -o 3DPrintDebug Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o $(IncludeThread) $(IncludeGraphics)
	mv 3DPrintDebug $(FolderExec)3DPrintDebug.out
3DGDBDebug:Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o
	$(Compiler) $(DebugMode) $(Arguments) -o 3DGDBDebug Color.o 3DBall.o 3DBoard.o Image.o 3DThreads.o $(IncludeThread) $(IncludeGraphics)
	mv 3DGDBDebug $(FolderExec)3DGDBDebug.out
	
Color.o: $(FolderCommon)Color.cpp
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp 
	# mv Color.o $(FolderObj)Color.o

3DBall.o: Color.o $(Folder3d)3DBall.cpp 
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp $(Folder3d)3DBall.cpp 
	# mv 3DBall.o $(FolderObj)3DBall.o

3DBoard.o: 3DBall.o $(Folder3d)3DBoard.cpp 
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp $(Folder3d)3DBall.cpp  $(Folder3d)3DBoard.cpp 
	# mv 3DBoard.o $(FolderObj)3DBoard.o

Image.o: $(FolderCommon)Image.cpp
	$(Compiler) $(Mode) $(Arguments) $(IncludingGraphics) $(FolderCommon)Image.cpp
	# mv Image.o $(FolderObj)Image.o

3DThreads.o: Image.o Color.o 3DBall.o 3DBoard.o $(Folder3d)3DThreads.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderCommon)Image.cpp $(FolderCommon)Color.cpp $(Folder3d)3DBall.cpp $(Folder3d)3DBoard.cpp $(Folder3d)3DThreads.cpp
	# mv 3DThreads.o $(FolderObj)3DThreads.o

Ball.o: $(FolderCommon)Ball.cpp Color.o
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp $(FolderCommon)Ball.cpp 
	# mv Ball.o $(FolderObj)Ball.o

Board.o: Ball.o $(FolderCommon)Board.cpp 
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Color.cpp $(FolderCommon)Ball.cpp $(FolderCommon)Board.cpp 
	# mv Board.o $(FolderObj)Board.o

Message.o: $(FolderCommon)Message.cpp
	$(Compiler) $(Mode) $(Arguments)  $(FolderCommon)Message.cpp
	# mv Message.o $(FolderObj)Message.o

2DThreads.o: Image.o Color.o Ball.o Board.o Message.o  $(FolderInter2D)2DThreads.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderCommon)Image.cpp $(FolderCommon)Color.cpp $(FolderCommon)Ball.cpp $(FolderCommon)Board.cpp  $(FolderCommon)Message.cpp $(FolderInter2D)2DThreads.cpp
	# mv Threads.o 2DThreads.o
	# mv 2DThreads.o $(FolderObj)2DThreads.o

2DThreadsMN.o: Image.o Color.o Ball.o Board.o Message.o $(FolderIndterMN2d)2DThreadsMN.cpp
	$(Compiler) $(Mode) $(Arguments) $(Including) $(IncludingGraphics)  $(FolderCommon)Image.cpp $(FolderCommon)Color.cpp $(FolderCommon)Ball.cpp $(FolderCommon)Board.cpp  $(FolderCommon)Message.cpp $(FolderIndterMN2d)2DThreadsMN.cpp
	# mv Threads.o 2DThreadsMN.o
	# mv Threads.o $(FolderObj)2DThreadsMN.o

2D: Image.o Color.o Ball.o Board.o Message.o 2DThreads.o
	$(Compiler) $(Arguments) -o 2D Color.o Ball.o Board.o Image.o  Message.o 2DThreads.o $(IncludeThread) $(IncludeGraphics) 
	mv 2D $(FolderExec)2D.out
2DPrintDebug: Image.o Color.o Ball.o Board.o Message.o 2DThreads.o
	$(Compiler) $(DebugDefine) $(Arguments) -o 2DPrintDebug Color.o Ball.o Board.o Image.o  Message.o 2DThreads.o $(IncludeThread) $(IncludeGraphics)
	mv 2DPrintDebug $(FolderExec)2DPrintDebug.out
2DGDBDebug: Image.o Color.o Ball.o Board.o Message.o 2DThreads.o
	$(Compiler) $(DebugMode) $(Arguments) -o 2DGDBDebug Color.o Ball.o Board.o Image.o  Message.o 2DThreads.o $(IncludeThread) $(IncludeGraphics)
	mv 2DGDBDebug $(FolderExec)2DGDBDebug.out

2DMN: Image.o Color.o Ball.o Board.o Message.o 2DThreadsMN.o
	$(Compiler) $(Arguments) -o 2DMN Color.o Ball.o Board.o Image.o  Message.o 2DThreadsMN.o $(IncludeThread) $(IncludeGraphics) 
	mv 2DMN $(FolderExec)2DMN.out
2DMNPrintDebug: Image.o Color.o Ball.o Board.o Message.o 2DThreadsMN.o
	$(Compiler) $(DebugDefine) $(Arguments) -o 2DMNPrintDebug Color.o Ball.o Board.o Image.o  Message.o 2DThreadsMN.o $(IncludeThread) $(IncludeGraphics)
	mv 2DMNPrintDebug $(FolderExec)2DMNPrintDebug.out
2DMNGDBDebug: Image.o Color.o Ball.o Board.o Message.o 2DThreadsMN.o
	$(Compiler) $(DebugMode) $(Arguments) -o 2DMNGDBDebug Color.o Ball.o Board.o Image.o  Message.o 2DThreadsMN.o $(IncludeThread) $(IncludeGraphics)
	mv 2DMNGDBDebug $(FolderExec)2DMNGDBDebug.out

Run3D: 3D
	cd $(FolderExec) ; ./3D.out $(num_thread)  
Run3DPrintDebug: 3DPrintDebug
	cd $(FolderExec) ; ./3DPrintDebug.out $(num_thread)  
Run3DGDBDebug: 3DGDBDebug
	cd $(FolderExec) ; gdb ./3DGDBDebug.out $(num_thread)  

Run2D: 2D
	cd $(FolderExec) ; ./2D.out $(num_thread)
Run2DPrintDebug: 2DPrintDebug
	cd $(FolderExec) ; ./2DPrintDebug.out $(num_thread)
Run2DGDBDebug: 2DGDBDebug
	cd $(FolderExec) ; gdb ./2DGDBDebug.out $(num_thread)

Run2DMN: 2DMN
	cd $(FolderExec) ; ./2DMN.out $(m) $(n)
Run2DMNPrintDebug: 2DMNPrintDebug
	cd $(FolderExec) ; ./2DMNPrintDebug.out $(m) $(n)
Run2DMNGDBDebug: 2DMNGDBDebug
	cd $(FolderExec) ; gdb ./2DMNGDBDebug.out $(m) $(n)

test: Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp  
	$(Compiler) $(Arguments)  Ball.cpp Board.cpp Test.cpp BallTest.cpp BoardTest.cpp AllTests.cpp 
	rm a.out 
	
clean:
	rm -rf Design\ document.pdf
	rm -rf Design\ document.log
	rm -rf Design\ document.aux
	rm -rf *.o
	rm -rf *.out
	rm -rf $(FolderObj)*.o
	rm -rf $(FolderExec)*.out
