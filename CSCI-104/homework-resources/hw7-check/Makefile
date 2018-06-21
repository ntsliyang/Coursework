CPPFLAGS = -g -Wall -std=c++11 
SUBFLAGS = -Wvla -Wshadow -Wunreachable-code -Wconversion
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: node_check bst_check iterator_check rotateBST_check

node_check: hw7_node_checker.cpp ../bst.h
	g++ $(CPPFLAGS) $(SUBFLAGS) $< -o $@

bst_check: hw7_bst_checker.cpp ../bst.h
	g++ $(CPPFLAGS) $(SUBFLAGS) $< -o $@

iterator_check: hw7_iterator_checker.cpp ../bst.h
	g++ $(CPPFLAGS) $(SUBFLAGS) $< -o $@

rotateBST_check: hw7_rotate_checker.cpp ../bst.h ../rotateBST.h
	g++ $(CPPFLAGS) $(SUBFLAGS) $< -o $@

bst_test: hw7_bst_test.cpp ../bst.h
	g++ $(CPPFLAGS) $< $(GTEST_LL) -o $@

rotate_test: hw7_rotate_test.cpp ../bst.h ../rotateBST.h
	g++ $(CPPFLAGS) $< $(GTEST_LL) -o $@

.PHONY: compile_check clean hypercube_test

compile_check:
	python3 checker.py

test: bst_test rotate_test
	-valgrind --tool=memcheck --leak-check=yes ./bst_test
	-valgrind --tool=memcheck --leak-check=yes ./rotate_test

hypercube_test:
	cd ..; make hypercube
	python3 hw7_cube.py

clean:
	-rm node_check
	-rm bst_check
	-rm iterator_check
	-rm rotateBST_check
	-rm bst_test
	-rm rotate_test