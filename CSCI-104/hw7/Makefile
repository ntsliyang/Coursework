CXX = g++
CPPFLAGS = -g -Wall
VERSION = -std=c++11

all: hypercube 

hypercube: hypercube.cpp 
	$(CXX) $(CPPFLAGS) $(VERSION) $^ -o $@

.PHONY: clean 
clean:
	rm -rf hypercube