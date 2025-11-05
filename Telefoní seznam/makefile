CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = telefon
SRC = main.c
OBJ = main.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

run: $(TARGET)
	./telefon 686 <seznam.txt

clean:
	rm -f $(OBJ) $(TARGET)
