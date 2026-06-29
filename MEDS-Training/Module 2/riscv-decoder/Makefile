# ............Compiler............
CC = gcc

# .........Compiler flags..........
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
DEBUG_FLAGS = -g -DDEBUG

# ...........Directories........
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# .........Source and object files........................
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# ...........Executable................
TARGET = $(BIN_DIR)/riscv-decoder

# ...............Test file..........................
TEST_FILE = test/programs/all_instructions.hex


#........... Build ............
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


#.......... Test....................

test: all
	./$(TARGET) $(TEST_FILE)


# ..................Debug Build......................
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# ...................Memory Leak Check...................
valgrind: all
	valgrind --leak-check=full \
	          --show-leak-kinds=all \
	          ./$(TARGET) $(TEST_FILE)

# ..................Clean..................
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)


.PHONY: all test debug valgrind clean
