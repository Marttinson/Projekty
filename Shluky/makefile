CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = Cluster
SRC = main.c
OBJ = main.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	
run: $(TARGET)
	./Cluster test.txt 20

clean:
	rm -f $(OBJ) $(TARGET)
