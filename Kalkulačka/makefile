# Makefile pro jednoduchý C program

TARGET = main
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

SRC = main.c
OBJ = $(SRC:.c=.o)

# Kompilace
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Překlad zdrojového kódu na objektový soubor
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Spuštění programu
run: $(TARGET)
	./$(TARGET)

# Vyčištění
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all run clean
all: $(TARGET)

