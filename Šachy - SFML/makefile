# Název výstupního souboru
TARGET = hra

# Kompilátor
CXX = g++

# Přepínače kompilátoru
CXXFLAGS = -Wall -Wextra -std=c++17

# Knihovny SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Soubory
SRCS = main.cpp Hra.cpp Policko.cpp
OBJS = $(SRCS:.cpp=.o)

# Pravidlo pro sestavení
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_LIBS)

# Pravidlo pro překlad jednotlivých .cpp souborů
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Vyčištění
clean:
	rm -f $(OBJS) $(TARGET)

# Spuštění programu
run: $(TARGET)
	./$(TARGET)

