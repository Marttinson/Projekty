#pragma once
#include "Drevo.h"

class Dreva
{
public:
    Dreva();

    int pocet_dreva;
    int index;

    Drevo* drevo;
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