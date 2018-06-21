# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all:$(BIN_DIR)/fibTest
	-@echo "--- All Built!---"

$(BIN_DIR)/fib.o: fib.cpp fib.h $(BIN_DIR)/.dirstamp	
	$(CC) $(CPPFLAGS) -c fib.cpp -o $(BIN_DIR)/fib.o

# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/fibTest: test.cpp $(BIN_DIR)/fib.o
	$(CC) $(CPPFLAGS) test.cpp $(BIN_DIR)/fib.o $(GTEST_LL) -o $(BIN_DIR)/fibTest

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

tests: $(BIN_DIR)/fibTest
	-@$(BIN_DIR)/fibTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
