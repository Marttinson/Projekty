#pragma once
#include "Hrac.h"
#include "NahodneCislo.h"
#include <iostream>
#include <string>

using namespace std;

class Boj : public NahodneCislo
{
public:
	Hrac hrac;
	string jmeno;
	int hp;
	int dmg;
	int odmena_za_zabiti;
	void souboj(string souper);
	void Glum();
	void Cezhar();
};

