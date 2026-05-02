# TODO: Clean this file up by creating separate variables for debug and release
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
BIN_NAME := isevenhelper
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: main

debug: CXXFLAGS += -g -O0
debug: main

main: $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/$(BIN_NAME) -lboost_program_options $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
