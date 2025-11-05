#include "Inventar.h"

Inventar::Inventar() {
	this->itemy = new Itemy;
	this->pocet_itemu = 0;
	this->velikost_inventare = 1;
}

Inventar::~Inventar() {
	if (this->pocet_itemu == 1 || this->pocet_itemu == 0)
		delete this->itemy;
	else
		delete[] this->itemy;
}

void Inventar::zvetseniInventare() {
	if (this->pocet_itemu == 1) {
		Itemy pomoc(itemy[0].nazev, itemy[0].pocet_brneni);

		delete this->itemy;
		this->itemy = new Itemy[2];
		this->itemy[0] = pomoc;
		this->velikost_inventare = 2;
	}
	else {
		Itemy* pomoc = new Itemy[this->pocet_itemu];

		for (int i = 0; i < this->pocet_itemu; i++)
			pomoc[i] = this->itemy[i];

		delete[] this->itemy;
		this->velikost_inventare *= 2;
		this->itemy = new Itemy[this->velikost_inventare];

		for (int i = 0; i < this->pocet_itemu; i++)
			this->itemy[i] = pomoc[i];

		delete[] pomoc;
	}
}

void Inventar::pridatDoInventare(Itemy item) {
	if (this->pocet_itemu == this->velikost_inventare) {
		zvetseniInventare();
	}
	
	this->itemy[this->pocet_itemu] = item;
	this->pocet_itemu++;
	item.vypisItemu();
}

void Inventar::vypisInventare() {
	if (this->pocet_itemu == 0)
		cout << "Inventar je prazdna\n";
	else {
		cout << "Tvoje inventar:\n--------------------------\n";
		for (int i = 0; i < this->pocet_itemu; i++) {
			cout << itemy[i].nazev << endl << "Brneni: " << itemy[i].pocet_brneni << endl << "--------------------------" << endl;
		}
	}
}

void Inventar::lootovani(int level) {
	Itemy item;
	this->pridatDoInventare(item.nahodnyItem(level));
}