# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall

all: listint_test

listint_test: listint.o listint_test.o
	g++ -g -Wall -o listint_test listint.o listint_test.o

# example using MAKE variables $(CC) is replaced with g++, etc.
listint.o: listint.h listint.cpp
	$(CC) $(CFLAGS) -c listint.cpp

listint_test.o: listint.h listint_test.cpp
	$(CC) $(CFLAGS) -c listint_test.cpp

clean:
	rm -f *.o listint_test *~

tarit:
	tar cvf listint.tar listint.h listint.cpp listint_test.cpp Makefile
	scp listint.tar redekopp@ee.usc.edu:Sites/cs103
