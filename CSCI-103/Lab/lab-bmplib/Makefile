# contact: Mark Redekopp, David Pritchard

CC = compile
# if needed, install from http://bits.usc.edu/cs103/compile/ or use g++ or clang++
LDFLAGS =
SRCS = shapes.cpp bmplib.cpp
OBJ = $(SRCS:.cpp=.o)
DEMOSRC = demo.cpp bmplib.cpp
DEMOOBJ = $(DEMOSRC:.cpp=.o)

all: shapes demo

demo: $(DEMOOBJ)
	$(CC) $(DEMOOBJ) -o demo

shapes: $(OBJ)
	$(CC) $(OBJ) -o shapes

.cpp.o:
	$(CC) -c $<

bmplib.o : bmplib.h

clean:
	rm -f *.o shapes *~

