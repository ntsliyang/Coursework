all: search

search: search.cpp webpage.o
	g++ -g -Wall -std=c++11 $^ -o $@

webpage.o: webpage.cpp webpage.h
	g++ -g -Wall -std=c++11 -c $< -o $@

.PHONY: clean
clean:
	rm search webpage.o