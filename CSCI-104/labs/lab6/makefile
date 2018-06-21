CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all: $(BIN_DIR)/order

$(BIN_DIR)/order: $(BIN_DIR)/order.o main.cpp
	$(CXX) $(CPPFLAGS) main.cpp $(BIN_DIR)/order.o -o $(BIN_DIR)/order

$(BIN_DIR)/order.o: $(BIN_DIR)/.dirstamp order.cpp order.h
	$(CXX) $(CPPFLAGS) -c order.cpp -o $(BIN_DIR)/order.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp