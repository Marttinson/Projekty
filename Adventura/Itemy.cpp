#include "Itemy.h"

Itemy::Itemy() {
	this->pocet_brneni = 0;
}

Itemy::Itemy(string nazev, int brneni) {
	this->nazev = nazev;
	this->pocet_brneni = brneni;
}

Itemy Itemy::nahodnyItem(int uroven_hrace) {
	int random = randomCislo(Items::pocet_itemu) - 1;

	string jmeno = Items::itemy[random];

	random = randomCislo(Items::pocet_itemu) - 1;
	int brneni = uroven_hrace + random;

	Itemy hotovo(jmeno, brneni);
	return hotovo;
}

void Itemy::vypisItemu() {
	cout << this->nazev << endl << "Brneni: " << this->pocet_brneni << endl;
}