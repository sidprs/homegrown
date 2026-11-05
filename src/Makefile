CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

TARGET = file

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

DEPS = $(wildcard *.h)

# Default target: builds the executable
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into a .o file
# This rule states that every .o file depends on its .c file AND all .h files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
.PHONY: all clean
clean:
	rm -f $(OBJS) $(TARGET)
