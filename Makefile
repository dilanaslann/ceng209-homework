# Makefile for Dungeon Adventure Game

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Output executable file
EXEC = dungeon_adventure

# Source files
SRC = dungeon_adventure.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target: build the executable
all: $(EXEC)

# Link the object files to create the final executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the compiled files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Run the game
run: $(EXEC)
	./$(EXEC)

# Save the game state after running
save: $(EXEC)
	./$(EXEC) save
