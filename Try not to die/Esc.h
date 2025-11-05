#pragma once
#include "Tlacitko.h"
#include "Textura.h"

class Esc
{
public:
	Textura pozadi;

	Tlacitko pokracovat;
	Tlacitko konec;

	void nastaveni(sf::Vector2f rozliseni);
	void update(sf::Vector2f pozice_kurzoru);
	void render(sf::RenderTarget* okno);
};