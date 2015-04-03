GCC_OPTIONS=-Wall -pedantic -I /include 

LIBS = -L/usr/lib -lGLEW -lglut -lGL -lGLU -lXext -lXmu -lX11 -lm 

INCS = -I/usr/include

all:
	g++ $(INCS) $(GCC_OPTIONS) shader.cpp texture.cpp controls.cpp objloader.cpp test.cpp -lGL -lGLU -lglut -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread  $(LIBS)
	./a.out

clean:
	rm -rf a.out
