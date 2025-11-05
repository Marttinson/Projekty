#pragma once
#include "Strela.h"
#include "Dreva.h"
#include "Kameny.h"
#include "Pozadi.h"
#include "Zombici.h"
#include "Hrac.h"

class Strelba
{
public:
	Strelba();

	Strela* strely;
	int pocet_strel;
	int zasobnik;
	int pauza;

	void render(sf::RenderTarget* okno);
	void update(sf::Clock cas, Dreva dreva, Kameny kameny, Pozadi pozadi, Zombici& zombici, Hrac* hrac);
	void pridat(sf::Vector2f souradnice, float uhel, sf::Vector2f pozice_kurzoru);
	void pohypProHrace(float x, float y);
};