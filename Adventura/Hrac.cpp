#include "Hrac.h"

Hrac::Hrac() {
	this->zlato = 10;
	this->level = 1;
}

void Hrac::loot() {
	Inventar::lootovani(this->level);
}
