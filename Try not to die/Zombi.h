#pragma once
#include "Textura.h"
#include "Pozadi.h"
#include "Kameny.h"
#include "Dreva.h"
#include "Hrac.h"

class Zombi
{
public:
	Zombi();
	Textura zombi;
	int pozice;
	std::string smer;
	int odpocet_pohybu;
	bool zije;

	bool prava;
	bool leva;
	bool nahore;
	bool dole;
	std::string strana;
	int posun;

	bool na_hit;
	int index_prvku;
	bool hit_kamen;
	bool hit_drevo;

	void spawn(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac, int index, sf::Vector2f* souradnice);
	bool kontrolaProSpawn(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac, int randomX, int randomY, int index, sf::Vector2f* souradnice);
	void render(sf::RenderTarget* okno);
	void update(Pozadi pozadi, Kameny& kameny, Dreva& dreva, Hrac* hrac);
	void pohybProHrace(float x, float y);
	void kontrolaPohybu(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac);
	void pohyb(Hrac* hrac);
};