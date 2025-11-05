#pragma once
#include "Zombi.h"
#include "Text.h"

class Zombici
{
public:
	Zombici();

	Text text;

	Zombi* zombici;
	int pocet_zombiku;
	int max_pocet_zombiku;
	int odpocet;
	int zabitych_zombiku;
	sf::Vector2f souradnice[10];

	void render(sf::RenderTarget* okno);
	void update(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac);
	void pohypProHrace(float x, float y);
	void spawn(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac);
	bool kontrolaProStrelu(sf::Vector2f souradnice);
};