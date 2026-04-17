SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

main: $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	g++ -o $(BIN_DIR)/$@ -lboost_program_options $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	g++ -c $< -o $@

clean:
	rm -rf $(BIN_DIR)
