#pragma once
#include "Stromy.h"
#include "Skaly.h"
#include "Hrac.h"

class Pozadi
{
public:
	Textura** prvek;
	int velikost_hraci_plochy;
	int pocet_stromu;
	int pocet_skal;

	Stromy stromy;
	Skaly skaly;

	void naplnPozadi(sf::Vector2f rozliseni, Hrac* hrac);
	void renderPozadi(sf::RenderTarget* okno);
	void pohyb(float x, float y);
	std::string pozadiNaSouradnici(float souradniceX, float souradniceY);
	bool jeTamStrom(float souradniceX, float souradniceY);
	bool jeTamSkala(float souradniceX, float souradniceY);
};