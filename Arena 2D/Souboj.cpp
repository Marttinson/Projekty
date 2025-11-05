#include "Souboj.h"

void Souboj::utokNaHrace1(Hrac hrac1, Hrac hrac2) {
	srand((unsigned)time(NULL));

	int nahoda;
	
	nahoda = 1 + rand() % hrac2.bojovnik.kritik;
	//cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = hrac2.bojovnik.dmg*2 - hrac1.bojovnik.obrana;
	}
	else {
		this->poskozeni = hrac2.bojovnik.dmg - hrac1.bojovnik.obrana;
	}

	nahoda = 1 + rand() % hrac1.bojovnik.vyhnuti;
	//cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = 0;
	}
	else {
		if (this->poskozeni > 0) {
			hrac1.bojovnik.hp -= this->poskozeni;
		}
		else {
			this->poskozeni = 0;
		}
	}
	//cout << this->poskozeni << endl;
	//cout << hrac1.bojovnik.hp;
}

void Souboj::utokNaHrace2(Hrac hrac1, Hrac hrac2) {
	srand((unsigned)time(NULL));

	int nahoda;

	nahoda = 1 + rand() % hrac1.bojovnik.kritik;
	cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = hrac1.bojovnik.dmg * 2 - hrac2.bojovnik.obrana;
	}
	else {
		this->poskozeni = hrac1.bojovnik.dmg - hrac2.bojovnik.obrana;
	}

	nahoda = 1 + rand() % hrac2.bojovnik.vyhnuti;
	cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = 0;
	}
	else {
		if (this->poskozeni > 0) {
			hrac2.bojovnik.hp -= this->poskozeni;
		}
		else {
			this->poskozeni = 0;
		}
	}
	cout << this->poskozeni << endl;
	cout << hrac2.bojovnik.hp;
}

void Souboj::pauza(Hrac hrac) {
	hrac.bojovnik.hp += hrac.bojovnik.pauza;

	if (hrac.bojovnik.hp > hrac.bojovnik.max_hp) {
		hrac.bojovnik.hp = hrac.bojovnik.max_hp;
		cout << BOLDWHITE << "Mas uz plne zivoty" << RESET << endl;
	}

	cout << BOLDWHITE << "Hrac " << BOLDGREEN << hrac.jmeno << BOLDWHITE << " ma " << hrac.bojovnik.hp << "hp" << RESET << endl;
}