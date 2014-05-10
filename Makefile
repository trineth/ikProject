CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Icode/glut-3.7.6-bin
	LDFLAGS = -lglut -lGL -lGLU
endif
	
RM = /bin/rm -f 
all: main
main: code/main.o code/point.o code/link.o
	$(CC) $(CFLAGS) -o main code/point.o code/link.o code/main.o $(LDFLAGS)

code/main.o: code/main.cpp code/point.cpp code/link.cpp
	$(CC) $(CFLAGS) -c code/main.cpp -o code/main.o

code/link.o: code/link.cpp
	$(CC) $(CFLAGS) -c code/link.cpp -o code/link.o

code/point.o: code/point.cpp
	$(CC) $(CFLAGS) -c code/point.cpp -o code/point.o

clean: 
	$(RM) *.o code/*.o main
 

