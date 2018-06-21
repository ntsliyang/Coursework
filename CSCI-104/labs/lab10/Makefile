CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/test

$(BIN_DIR)/test: test.cpp $(BIN_DIR)/EdgeSet.o $(BIN_DIR)/AdjList.o $(BIN_DIR)/AdjMatrix.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/AdjList.o: AdjList.cpp AdjList.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/AdjMatrix.o: AdjMatrix.cpp AdjMatrix.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/EdgeSet.o: EdgeSet.cpp EdgeSet.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/.dirstamp:
	-@mkdir $(BIN_DIR)
	-@touch $(BIN_DIR)/.dirstamp

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

test: $(BIN_DIR)/test
	-@./$(BIN_DIR)/test