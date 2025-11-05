#pragma once
#include "Textura.h"

class Zvuk
{
public:
	sf::SoundBuffer buffer;
	sf::Sound zvuk;

	void nastaveni(std::string cesta, int hlasitost);
};