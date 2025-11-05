#pragma once
#include "Itemy.h"
#include <iostream>
#include <string>

using namespace std;

class Inventar
{
public:
	Inventar();
	~Inventar();
	Itemy *itemy;
	int pocet_itemu;
	int velikost_inventare;
	void zvetseniInventare();
	void pridatDoInventare(Itemy item);
	void vypisInventare();
	void lootovani(int level);
};

