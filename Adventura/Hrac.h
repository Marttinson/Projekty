#pragma once
#include "Bojovnik.h"
#include "Inventar.h"
#include <string>

using namespace std;

class Hrac : public Inventar
{
public:
	Hrac();
	Bojovnik bojovnik;
	string jmeno;
	int level;
	int zlato;
	void loot();
	void obchodnik();
};

