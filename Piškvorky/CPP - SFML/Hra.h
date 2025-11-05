#pragma once

#include <iostream>

#include "Tlacitko.h"

class Hra
{
private:
	//privatni promeny
	//okno
	sf::RenderWindow* okno;
	sf::VideoMode video;
	sf::Event ev;

	//menu
	Tlacitko zacit_hru;
	Tlacitko nastaveni;
	Tlacitko setVelikost;
	Tlacitko setVyhru;
	Tlacitko back;
	Tlacitko konec;
	
	//myška
	sf::Vector2f pozice_kurzoru;

	//text
	sf::Font font;
	sf::Text text;

	//tlacitka
	int velikost;
	Tlacitko** tlacitka;
	bool jednou;
	int tah;
	int na_vyhru;
	bool vyhrano;
	bool hra_zacala;
	bool nas;
	bool vykresleno;

	//nastaveni hodnot, vola je konstruktor
	void nastaveniOkna();
	void nastaveniFont();
	void nastaveniText();

public:
	//kunstruktor a dekostruktor
	Hra();
	~Hra();

	//promeny

	//funkce
	void menu();
	void funkceNastaveni();
	void hraj();
	void render();
	void renderPole();
	void update();
	void updatePole();
	void vyplneniPole(int x, int y);
	void kurzorUpdate();
	void eventLoop();
	void vykresleniPole(int velikost);
	void exit();

	//vyhry
	bool vodorovne(int _x, int _y, std::string znak);
	bool svisle(int _x, int _y, std::string znak);
	bool sikmo1(int _x, int _y, std::string znak);
	bool sikmo2(int _x, int _y, std::string znak);

	//gettery
	bool running();
	//settery
};

