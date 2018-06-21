CPPFLAGS = -g -Wall -std=c++11 
SUBFLAGS = -Wvla -Wshadow -Wunreachable-code -Wconversion
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: main splay-test edge

main: main.cpp 
	g++ $(CPPFLAGS) $< -o $@ -pg

splay-test: splay-test.cpp 
	g++ $(CPPFLAGS) $< -o $@

edge: edge.cpp splayTree.h
	g++ $(CPPFLAGS) $(SUBFLAGS) $< $(GTEST_LL) -o $@

.PHONY: clean
clean: 
	rm -rf main splay-test edge