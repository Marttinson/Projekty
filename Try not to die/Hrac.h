#pragma once
#include "Textura.h"
#include "Text.h"

#include "Inventar.h"

class Hrac :
	public Textura
{
public:
	int hp;
	Text txt_hp;
	bool na_skale;

	Inventar* inv;
	sf::RectangleShape vybrana_pozice;

	Textura pistol[2];
	Textura sekera;
	Textura krumpac;

	Hrac(sf::Vector2f velikost);
	~Hrac();
	void naplneniInv(sf::Vector2f velikost);
	void vybranejItem(int poradi);
	void render(sf::RenderTarget* okno);
};