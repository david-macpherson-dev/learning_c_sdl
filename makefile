# ---  Compiler options  ---

# Set the compiler
CC := gcc

# Set the compiler flags
CFLAGS := `sdl2-config --libs --cflags`

# --------------------------


# -------   Inputs    ------

# Add header files
HEADERS := 

# Add srouce files
SRCS := $(wildcard src/*.c)

# --------------------------


# ------   Outputs    ------

# Add bin folder location
BIN_DIR := bin

# Name of executable
EXEC := window

# --------------------------

# -------   Recipes   ------

all:
	mkdir -p bin
	$(CC) $(SRCS) -o $(BIN_DIR)/$(EXEC) $(CFLAGS)

clean:
	rm -rf $(BIN_DIR) $(OBJS)

.PHONY: all clean
# --------------------------
