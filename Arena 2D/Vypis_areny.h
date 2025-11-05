#ifndef __VYPIS_ARENY_H_
#define __VYPIS_ARENY_H_
#include <iostream>
#include <string>
#include "Hrac.h"


using namespace std;

class Vypis_areny {
public:
	void uvitani();
	Hrac hrac1, hrac2;
	const int zakladni_pozice1 = 8;		//7
	const int zakladni_pozice2 = 16;	//17
	int pozice1;
	int pozice2;
	const int sirka = 25;
	const int vyska = 5;
	char arena[5][25];
	void zalozeni(Hrac hrac1, Hrac hrac2);
	void vypis();
	void pohyb(Hrac hrac);
	void vyberAkce(Hrac hrac1, Hrac hrac2);
	string vyber_akce;
	char strana;
};
#endif