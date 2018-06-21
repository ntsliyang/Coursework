all: Thanksgiving.o LengthMismatch.o

LengthMismatch.o: LengthMismatch.cpp LengthMismatch.h 
	g++ -g -Wall -std=c++11 -c $< -o $@

Thanksgiving.o: Thanksgiving.cpp LengthMismatch.h
	g++ -g -Wall -std=c++11 -c $< -o $@

.PHONY: clean
clean:
	rm Thanksgiving.o LengthMismatch.o