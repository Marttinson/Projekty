#pragma once
#include <string>
#include <iostream>
#include "Items.h"
#include "NahodneCislo.h"

using namespace std;

class Itemy : public Items, public NahodneCislo
{
public:
	Itemy();
	Itemy(string nazev, int brneni);
	string nazev;
	int pocet_brneni;
	Itemy nahodnyItem(int uroven_hrace);
	void vypisItemu();
};

