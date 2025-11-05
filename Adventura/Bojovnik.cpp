#include "Bojovnik.h"

void Bojovnik::vypisTrid() {
	cout << "1.Valecnik \n2.Lukostrelec \n3.Kouzlenik \n";
}

void Bojovnik::urceniTridy() {
	this->vypisTrid();
	cin >> this->vyber;
	

	if (this->vyber == "1" || this->vyber == "Valecnik" || this->vyber == "valecnik") {
		this->valecnik();
	}
	else if (this->vyber == "2" || this->vyber == "Lukostrelec" || this->vyber == "lukostrelec") {
		this->lukostrelec();
	}
	else if (this->vyber == "3" || this->vyber == "Kouzlenik" || this->vyber == "kouzlenik") {
		this->kouzelnik();
	}
}

void Bojovnik::valecnik() {
	this->nazev = "Valecnik";
	this->hp = 50;
	this->obrana = 10;
	this->utok = 5;
}

void Bojovnik::lukostrelec() {
	this->nazev = "Lukostrelec";
	this->hp = 40;
	this->obrana = 8;
	this->utok = 8;
}

void Bojovnik::kouzelnik() {
	this->nazev = "Kouzelnik";
	this->hp = 30;
	this->obrana = 5;
	this->utok = 10;
}