# Makefile pro jednoduchý C++ program

# Nastavení názvu cílového souboru
TARGET = main

# Compiler a flagy pro kompilaci
CXX = g++
CXXFLAGS = -Wall -g

# Zdrojový soubor
SRC = main.cpp

# Objektové soubory
OBJ = $(SRC:.cpp=.o)

# Cíl pro kompilaci
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Cíl pro spuštění programu
run: $(TARGET)
	./$(TARGET)

# Cíl pro čištění
clean:
	rm -f $(TARGET) $(OBJ)

# Vytvoření objektového souboru
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Defaultní cíl
.PHONY: all run clean
all: $(TARGET)

