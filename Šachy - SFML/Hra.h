#pragma once

#include <iostream>

#include "Policko.h"

class Hra
{
private:
	//privatni promeny
	bool zmacknuto;
	bool jednou;
	int pocet_kol;
	std::string barva;

	sf::Text text[16];
	sf::Font font;

	//okno
	sf::RenderWindow* okno;
	sf::VideoMode video;
	sf::Event ev;

	//policka
	Policko** hraci_plocha;
	sf::Texture nic;

	int x;
	int y;

public:
	//kunstruktor a dekostruktor
	Hra();
	~Hra();

	//nastaveni hodnot, vola je konstruktor
	void nastaveniOkna();
	void nastaveniFont();
	void nastaveniText();

	//myška
	sf::Vector2f pozice_kurzoru;
	void kurzorUpdate();
	
	//promeny

	//funkce
	void hraj();
	void render();
	void update();
	void eventLoop();
	void renderText();

	//hraci plocha
	void naplneniHraciPlochy();
	void vykresleniHraciPlochy();
	void updateHraciPlochy();
	void zbarveniHraciPlochy();
	void vyplnFigurek();
	void updatePindu();
	void prirazeniBarvy();

	//pohyby
	void pohybPinda(int x, int y);
	void pohybVez(int x, int y);
	void pohybKun(int x, int y);
	void pohybStrelec(int x, int y);
	void pohybKralovna(int x, int y);
	void pohybKral(int x, int y);

	void pohyb(int posunX, int posunY, int x, int y);

	//gettery
	bool running();
	//settery
};

