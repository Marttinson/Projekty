#ifndef __INTERAKCE_H_
#define __INTERAKCE_H_
#include <iostream>
#include <string>
#include "Kostka.h"
#include "Bojovnici.h"
#include "Hrac.h"
#include "Souboj.h"

using namespace std;

class Interakce{
public:
	//void pocet_sten_kostky(Kostka &kostka);
	void vyber_postavu();
	Hrac hrac;
	void zalozeni_hrace(int i);
	Kostka kostka;
};

#endif