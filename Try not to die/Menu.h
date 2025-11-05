#pragma once
#include "Textura.h"
#include "Tlacitko.h"

class Menu
{
public:
	Menu();

	Textura pozadi;
	Text nadpis;

	Tlacitko nova_hra;
	Tlacitko konec;

	void render(sf::RenderTarget* okno);
	void nastaveni(sf::Vector2f rozliseni);
	void update(sf::Vector2f pozice_kurzoru);
};