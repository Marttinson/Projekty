#include "Bojovnici.h"

void Bojovnici::Valecnik() {
	this->pozice = 1;
	this->jmeno = "Valecnik";
	this->hp = 50;
	this->max_hp = hp;
	this->obrana = 4;
	this->dmg = 5;
	this->pocet_policek = 1;
	this->kritik = 2;			//50%
	this->vyhnuti = 10;			//10%
	this->pauza = max_hp / 10;
	this->vzdalenost = 1;
}

void Bojovnici::vypisValecnika() {
	Valecnik();

	cout << BOLDWHITE << pozice << "." << jmeno << ":" << GREEN <<" hp: " << hp << CYAN <<  " obrana: " << obrana << BOLDRED << " utok: " << dmg << BOLDMAGENTA << " uhyb: " << 100 / vyhnuti << "%" << BOLDBLUE << " kritik: " << 100 / kritik << "% " << BOLDYELLOW << "za jedno kolo pauzy ziska: " << pauza << " hp" << RESET << endl;
}

void Bojovnici::Lovec() {
	this->pozice = 2;
	this->jmeno = "Lovec";
	this->hp = 40;
	this->max_hp = hp;
	this->obrana = 4;
	this->dmg = 5;
	this->pocet_policek = 1;
	this->kritik = 5;			//20%
	this->vyhnuti = 2;			//50%
	this->pauza = max_hp / 10;
	this->vzdalenost = 1;
}

void Bojovnici::vypisLovce() {
	Lovec();

	cout << BOLDWHITE << pozice << "." << jmeno << ":" << GREEN << " hp: " << hp << CYAN << " obrana: " << obrana << BOLDRED << " utok: " << dmg << BOLDMAGENTA << " uhyb: " << 100 / vyhnuti << "%" << BOLDBLUE << " kritik: " << 100 / kritik << "% " << BOLDYELLOW << "za jedno kolo pauzy ziska: " << pauza << " hp" << RESET << endl;
}

void Bojovnici::Kouzelnik() {
	this->pozice = 3;
	this->jmeno = "Kouzelnik";
	this->hp = 30;
	this->max_hp = hp;
	this->obrana = 4;
	this->dmg = 5;
	this->pocet_policek = 1;
	this->kritik = 2;		//50%
	this->vyhnuti = 4;		//25%
	this->pauza = max_hp / 10;
	this->vzdalenost = 1;
}

void Bojovnici::vypisKouzelnika() {
	Kouzelnik();

	cout << BOLDWHITE << pozice << "." << jmeno << ":" << GREEN << " hp: " << hp << CYAN << " obrana: " << obrana << BOLDRED << " utok: " << dmg << BOLDMAGENTA << " uhyb: " << 100 / vyhnuti << "%" << BOLDBLUE << " kritik: " << 100 / kritik << "% " << BOLDYELLOW << "za jedno kolo pauzy ziska: " << pauza << " hp" << RESET << endl;
}