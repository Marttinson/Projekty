# Název výsledného programu
TARGET = main

# Kompilátor a jeho volby
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Zdrojové soubory
SRC = main.cpp Bojovnici.cpp Interakce.cpp Kostka.cpp Souboj.cpp

# Přeložené soubory (objektové)
OBJ = main.o Bojovnici.o Interakce.o Kostka.o Souboj.o

# Jak vytvořit spustitelný soubor
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Jak přeložit jednotlivé .cpp soubory
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Bojovnici.o: Bojovnici.cpp Bojovnici.h
	$(CXX) $(CXXFLAGS) -c Bojovnici.cpp -o Bojovnici.o

Interakce.o: Interakce.cpp Interakce.h
	$(CXX) $(CXXFLAGS) -c Interakce.cpp -o Interakce.o

Kostka.o: Kostka.cpp Kostka.h
	$(CXX) $(CXXFLAGS) -c Kostka.cpp -o Kostka.o

Souboj.o: Souboj.cpp Souboj.h
	$(CXX) $(CXXFLAGS) -c Souboj.cpp -o Souboj.o

# Spuštění programu
run: $(TARGET)
	./$(TARGET)

# Vyčištění nepotřebných souborů
clean:
	rm -f $(TARGET) $(OBJ)

# Říká, že tyto názvy nejsou skutečné soubory, ale příkazy
.PHONY: run clean

