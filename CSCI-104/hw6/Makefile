all: search crawler

search: search.cpp webpage.o
	g++ -g -Wall -std=c++11 $^ -o $@ -O2

webpage.o: webpage.cpp webpage.h
	g++ -g -Wall -std=c++11 -c $< -o $@ -O2

crawler: crawler.cpp
	g++ -g -Wall -std=c++11 $^ -o $@ -O2

.PHONY: clean
clean:
	rm -rf search 
	rm -rf webpage.o
	rm -rf crawler