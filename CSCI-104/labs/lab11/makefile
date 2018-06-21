all: sudoku example1

example1: example1.cpp
	g++ -g -Wall example1.cpp -o example1

sudoku: sudoku.o main.cpp
	g++ -g -Wall main.cpp sudoku.o -o sudoku

sudoku.o: sudoku.cpp sudoku.h
	g++ -g -Wall -c sudoku.cpp -o sudoku.o

clean:
	-@rm example1 
	-@rm sudoku 
	-@rm sudoku.o