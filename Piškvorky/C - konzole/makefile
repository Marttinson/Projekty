# Makefile pro jednoduchý program

# Nastavení názvu cílového souboru
TARGET = main

# Compiler a flagy pro kompilaci
CC = gcc
CFLAGS = -Wall -g

# Zdrojový soubor
SRC = main.c

# Objektové soubory
OBJ = $(SRC:.c=.o)

# Cíl pro kompilaci
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Cíl pro spuštění programu
run: $(TARGET)
	./$(TARGET)

# Cíl pro čištění
clean:
	rm -f $(TARGET) $(OBJ)

# Vytvoření objektového souboru
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Defaultní cíl
.PHONY: all run clean
all: $(TARGET)

