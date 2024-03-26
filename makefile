CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
INC_DIR=include

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
EXECUTABLE=$(BIN_DIR)/tarsau

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir --p $(OBJ_DIR)

$(BIN_DIR):
	@if [ ! -d "$(BIN_DIR)" ]; then mkdir --p $(BIN_DIR); fi

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
