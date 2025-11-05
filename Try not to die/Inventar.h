#pragma once
#include "Textura.h"
#include "Text.h"

#include <iostream>

class Inventar :
    public Textura
{
private:
    int poradi;
    int pocet;

    Text txt_poradi;
    Text txt_pocet;

public:
    Inventar();

    void zalozeniInv(int poradi, std::string cesta, float x, float y, bool je_tak = false);
    void setPocet(int pocet);
    void render(sf::RenderTarget* okno);
};