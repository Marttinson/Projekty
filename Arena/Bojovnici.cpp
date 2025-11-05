#include "Bojovnici.h"

void Bojovnici::Valecnik() {
	this->jmeno = "Valecnik";
	this->hp = 50;
	this->max_hp = hp;
	this->obrana = 6;
	this->dmg = 4;
}

void Bojovnici::Lovec() {
	this->jmeno = "Lovec";
	this->hp = 40;
	this->max_hp = hp;
	this->obrana = 5;
	this->dmg = 5;
}

void Bojovnici::Kouzelnik() {
	this->jmeno = "Kouzelnik";
	this->hp = 30;
	this->max_hp = hp;
	this->obrana = 4;
	this->dmg = 6;
}