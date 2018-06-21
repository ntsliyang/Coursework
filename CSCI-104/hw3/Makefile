all: stringparser

stringparser: stringparser.cpp lliststr.o stackstr.o
	g++ -g -Wall -std=c++11 $^ -o $@

stackstr.o: stackstr.cpp stackstr.h
	g++ -g -Wall -std=c++11 -c $< -o $@

lliststr.o: lliststr.cpp lliststr.h
	g++ -g -Wall -std=c++11 -c $< -o $@

.PHONY: clean
clean:
	rm stackstr.o lliststr.o stringparser