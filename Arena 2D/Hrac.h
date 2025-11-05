#ifndef __HRAC_H_
#define __HRAC_H_
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "Bojovnici.h"

using namespace std;

class Hrac {
public:
	void zalozeniHrace(int poradi);
	string jmeno;
	Bojovnici bojovnik;
	int poradi;
	char znak[20];
	string vyber_bojovnika;
	void utokNaHrace1(Hrac hrac1, Hrac hrac2);
	void utokNaHrace2(Hrac hrac1, Hrac hrac2);
	int poskozeni;
	void pauza();
};

#endif