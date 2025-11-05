# Název výsledného programu
TARGET = main

# Kompilátor a jeho volby
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Zdrojové soubory
SRC = main.cpp Bojovnici.cpp Hrac.cpp Souboj.cpp Vypis_areny.cpp

# Přeložené soubory (objektové)
OBJ = main.o Bojovnici.o Hrac.o Souboj.o Vypis_areny.o

# Vytvoření spustitelného souboru
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Překlad jednotlivých souborů
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Bojovnici.o: Bojovnici.cpp Bojovnici.h
	$(CXX) $(CXXFLAGS) -c Bojovnici.cpp -o Bojovnici.o

Hrac.o: Hrac.cpp Hrac.h
	$(CXX) $(CXXFLAGS) -c Hrac.cpp -o Hrac.o

Souboj.o: Souboj.cpp Souboj.h
	$(CXX) $(CXXFLAGS) -c Souboj.cpp -o Souboj.o

Vypis_areny.o: Vypis_areny.cpp Vypis_areny.h
	$(CXX) $(CXXFLAGS) -c Vypis_areny.cpp -o Vypis_areny.o

# Spuštění programu
run: $(TARGET)
	./$(TARGET)

# Vyčištění nepotřebných souborů
clean:
	rm -f $(TARGET) $(OBJ)

# Označení příkazů, které nejsou soubory
.PHONY: run clean

