# Název výstupního souboru
TARGET = hra

# Kompilátor
CXX = g++

# Přepínače kompilátoru
CXXFLAGS = -Wall -Wextra -std=c++17

# Knihovny SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Soubory
SRCS = main.cpp \
       Dreva.cpp Drevo.cpp Esc.cpp Hra.cpp Hrac.cpp Inventar.cpp \
       Kamen.cpp Kameny.cpp Menu.cpp Ovladani.cpp Pozadi.cpp \
       Skala.cpp Skaly.cpp Strela.cpp Strelba.cpp Strom.cpp Stromy.cpp \
       Text.cpp Textura.cpp Tlacitko.cpp Zombi.cpp Zombici.cpp Zvuk.cpp
       
OBJS = $(SRCS:.cpp=.o)

# Pravidlo pro sestavení
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_LIBS)

# Pravidlo pro překlad jednotlivých .cpp souborů
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Vyčištění
clean:
	rm -f $(OBJS) $(TARGET)

# Spuštění programu
run: $(TARGET)
	./$(TARGET)

