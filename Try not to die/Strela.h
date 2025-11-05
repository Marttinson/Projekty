#pragma once
#include <cmath>
#include "Textura.h"
#include "Zvuk.h"

class Strela
{
public:
	Strela();
	Textura strela;
	bool vystreleno;
	sf::Vector2f cil;
	sf::Vector2f posun;
	Zvuk zvuk;

	void render(sf::RenderTarget* okno);
	void update(sf::Clock cas);
	void nastaveni(sf::Vector2f souradnice, float uhel, sf::Vector2f pozice_kurzoru);
	void pohybProHrace(float x, float y);
	void pohyb(sf::Clock cas);
};
