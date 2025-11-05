#pragma once
#include "Pozadi.h"
#include "Hrac.h"
#include "Dreva.h"
#include "Kameny.h"
#include "Strelba.h"
#include "Zombici.h"
#include "Strelba.h"
#include "Zvuk.h"

#define _USE_MATH_DEFINES
#include <math.h>


class Ovladani
{
public:
	Ovladani();
	bool zmacknuto;
	std::string pohyb;
	std::string vybrano;
	int poradi_vybraneho;

	Zvuk kaceni_stromu;
	Zvuk tezeni_kamene;
	Zvuk pokladani_dreva;
	Zvuk pokladani_kamene;
	
	void updateTlacitek(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, sf::Event ev, double uhel, sf::Vector2f pozice_kurzoru, Strelba& strelba, Zombici& zombici);

	void tlacitkoW(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba);
	void tlacitkoS(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba);
	void tlacitkoA(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba);
	void tlacitkoD(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba);
	void tlacitkoMezernik(Pozadi& pozadi, Hrac* hrac);

	void tlacitko1(Hrac* hrac, double uhel);
	void tlacitko2(Hrac* hrac, double uhel);
	void tlacitko3(Hrac* hrac, double uhel);
	void tlacitko4(Hrac* hrac, double uhel);
	void tlacitko5(Hrac* hrac, double uhel);

	bool kontrolaUmisteni(std::string material, Pozadi pozadi, Dreva dreva, Kameny kameny, Hrac* hrac, sf::Vector2f pozice_kurzoru);
	void levyTlacitko(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, double uhel, sf::Vector2f pozice_kurzoru, Strelba& strelba);
};