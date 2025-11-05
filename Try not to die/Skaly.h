#pragma once
#include "Skala.h"

class Skaly
{
public:
    Skaly();

    Skala* prvek;
    int pocet_prvku;
    int velikost_pole;

    void zvetseniPole();
    bool kontrola(sf::Vector2f souradnice);
    void pridatPrvek(sf::Vector2f souradnice);
    void pohyb(float x, float y);
    void render(sf::RenderTarget* okno);
};