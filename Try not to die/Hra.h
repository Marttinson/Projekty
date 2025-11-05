#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

#include "Pozadi.h"
#include "Hrac.h"
#include "Dreva.h"
#include "Kameny.h"
#include "Stromy.h"
#include "Skaly.h"
#include "Ovladani.h"
#include "Menu.h"
#include "Esc.h"
#include "Strelba.h"
#include "Zombici.h"

class Hra
{
private:
	//okno
	sf::RenderWindow* okno;
	sf::Vector2f rozliseni;
	sf::VideoMode video;
	sf::Event ev;

	Pozadi pozadi;
	Ovladani ovladani;
	Esc esc;

	sf::Vector2f pozice_kurzoru;

	Dreva dreva;
	Kameny kameny;

	Zombici zombici;

	Hrac* hrac;
	double uhel;
	sf::Clock cas_na_pohyb;
	int poradi_vybraneho;
	Strelba strelba;

	Menu menu;
	bool vMenu;
	bool ESC;
	bool veHre;
	bool jednou;

	bool konec;
	Tlacitko koncici_tlacitko;
	Text koncici_text;
	Textura hrob;

public:
	//kunstruktor a dekostruktor
	Hra();
	~Hra();

	void nastaveniOkna();


	//funkce
	void hraj();
	void startHry();

	void render();
	void renderGear();

	void update();
	void eventLoop();
	void updateKurzor();
	void updateMenu();
	void updateTlacitkaESC();
	void updateESC();
	void updateTextu();

	void konecHry();
	
	bool running();
};
