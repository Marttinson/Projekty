#pragma once
#include "Kamen.h"

class Kameny
{
public:
	Kameny();

    int pocet_kamene;
    int index;

    Kamen* kamen;
    int pocet_prvku;
    int velikost_pole;

    void zvetseniPole();
    void pridatPrvek(sf::Vector2f mys);
    bool zkontrolovat(sf::Vector2f mys);
    bool kontrolaPrekryti(float x, float y);
    bool kontrolaPrekryti(sf::Vector2f souradnice);
    void pohyb(float x, float y);
    void render(sf::RenderTarget* okno);
};