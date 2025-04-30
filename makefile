# Compiler to use
CC = gcc
# Compiler flags (add SDL include path)
CFLAGS = -Wall -g -I/usr/include/SDL

# Linker flags (include SDL 1.2, SDL_mixer 1.2, math, threading, SDL_ttf, SDL_image)
LDFLAGS = -lSDL -lSDL_mixer -pthread -lm -lSDL_ttf -lSDL_image

# Target executable name
TARGET = game

# Find all .c files in the current directory
SOURCES = $(wildcard *.c)
# Generate object file names from source files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
