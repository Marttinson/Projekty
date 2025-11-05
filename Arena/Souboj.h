#ifndef __SOUBOJ_H_
#define __SOUBOJ_H_
#include <iostream>
#include "Bojovnici.h"
#include "Hrac.h"
#include "Kostka.h"
#include "Interakce.h"

using namespace std;

class Souboj{
public:
	void bitva(Hrac &hrac1, Hrac &hrac2);
	int hod_hrace1;
	int hod_hrace2;
	int poskozeni_hrace1;
	int poskozeni_hrace2;
	int obrana_hrace1;
	int obrana_hrace2;
	void vypis_bitvy(Hrac &hrac1, Hrac &hrac2);
	Kostka kostka1;
	Kostka kostka2;
};

#endif