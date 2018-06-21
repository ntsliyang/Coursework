# Makefile for EDITS BST test suite

BINDIR := bin
HW8_DIR := ../

# check environment variable - https://stackoverflow.com/questions/4728810/makefile-variable-as-prerequisite
ifndef HW8_DIR
  $(error HW8_DIR is undefined!  Please set it to point to your hw8 subdir!)
endif

CXX := g++
CXXFLAGS := -g -Wall -Wextra -Wconversion -Wvla -Wshadow -Wunreachable-code --std=c++11 -I$(HW8_DIR)

VALGRIND := valgrind --tool=memcheck --leak-check=yes

GTEST_CXXFLAGS := -I /usr/include/gtest/ 
GTEST_LDFLAGS := -l gtest -l gtest_main -pthread

HEADERS := splay_tests.h create_bst.h check_bst.h print_bst.h user_bst_headers.h check_splay.h create_splay.h \
	$(HW8_DIR)/bst.h $(HW8_DIR)/rotateBST.h $(HW8_DIR)/splayTree.h

all: splay_tester test

# Create binary dir
$(BINDIR)/.dirstamp:
	mkdir -p $(BINDIR)
	touch $(BINDIR)/.dirstamp

# generic rule for .cpp files
$(BINDIR)/%.o : %.cpp $(BINDIR)/.dirstamp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) $(GTEST_CXXFLAGS) $< -o $@

splay_tester: $(BINDIR)/test_insert.o  $(BINDIR)/test_remove.o $(BINDIR)/test_minmax.o $(BINDIR)/test_find.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LDFLAGS)

clean:
	rm -rf splay_tester $(BINDIR)

# run tests!
test: splay_tester
	$(VALGRIND) ./splay_tester