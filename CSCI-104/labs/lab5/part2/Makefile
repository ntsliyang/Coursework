# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/arrayTest: test.cpp $(BIN_DIR)/arraylist.o
	$(CC) $(CPPFLAGS) test.cpp $(BIN_DIR)/arraylist.o $(GTEST_LL) -o $(BIN_DIR)/arrayTest

.PHONY: tests clean

tests: $(BIN_DIR)/arrayTest
	-@$(BIN_DIR)/arrayTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)/arrayTest
	-@echo "--- All Clean!---"