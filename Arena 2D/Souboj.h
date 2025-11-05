#ifndef __SOUBOJ_H_
#define __SOUBOJ_H_
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include "Hrac.h"

using namespace std;

class Souboj{
public:
	void utokNaHrace1(Hrac hrac1, Hrac hrac2);
	void utokNaHrace2(Hrac hrac1, Hrac hrac2);
	int poskozeni;
	void pauza(Hrac hrac);
};

#endif