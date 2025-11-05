# Název výsledného programu
TARGET = main

# Kompilátor a jeho volby
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Zdrojové soubory
SRC = main.cpp Boj.cpp Bojovnik.cpp Hra.cpp Hrac.cpp Inventar.cpp Itemy.cpp Mapa.cpp NahodneCislo.cpp

# Přeložené soubory (objektové)
OBJ = main.o Boj.o Bojovnik.o Hra.o Hrac.o Inventar.o Itemy.o Mapa.o NahodneCislo.o

# Vytvoření spustitelného souboru
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Překlad jednotlivých souborů
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Boj.o: Boj.cpp Boj.h
	$(CXX) $(CXXFLAGS) -c Boj.cpp -o Boj.o

Bojovnik.o: Bojovnik.cpp Bojovnik.h
	$(CXX) $(CXXFLAGS) -c Bojovnik.cpp -o Bojovnik.o

Hra.o: Hra.cpp Hra.h
	$(CXX) $(CXXFLAGS) -c Hra.cpp -o Hra.o

Hrac.o: Hrac.cpp Hrac.h
	$(CXX) $(CXXFLAGS) -c Hrac.cpp -o Hrac.o

Inventar.o: Inventar.cpp Inventar.h
	$(CXX) $(CXXFLAGS) -c Inventar.cpp -o Inventar.o

Itemy.o: Itemy.cpp Items.h
	$(CXX) $(CXXFLAGS) -c Itemy.cpp -o Itemy.o

Mapa.o: Mapa.cpp Mapa.h
	$(CXX) $(CXXFLAGS) -c Mapa.cpp -o Mapa.o

NahodneCislo.o: NahodneCislo.cpp NahodneCislo.h
	$(CXX) $(CXXFLAGS) -c NahodneCislo.cpp -o NahodneCislo.o

# Spuštění programu
run: $(TARGET)
	./$(TARGET)

# Vyčištění nepotřebných souborů
clean:
	rm -f $(TARGET) $(OBJ)

# Označení příkazů, které nejsou soubory
.PHONY: run clean

