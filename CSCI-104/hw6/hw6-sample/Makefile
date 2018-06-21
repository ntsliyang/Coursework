all: search crawler

search: search.cpp webpage.o
	g++ -g -Wall -std=c++11 $^ -o $@

webpage.o: webpage.cpp webpage.h
	g++ -g -Wall -std=c++11 -c $< -o $@

crawler: crawler.cpp
	g++ -g -Wall -std=c++11 $^ -o $@

.PHONY: clean
clean:
	rm -rf search 
	rm -rf webpage.o
	rm -rf crawler