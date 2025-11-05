#include "Kamen.h"

//Inicializace promìnných
Kamen::Kamen() {
	this->nastaveniKamene();
	this->hp = 10;
}

//Funkce která umístí kámen na požadované souøadnice
void Kamen::umisteni(sf::Vector2f mys) {
	this->setPos(mys.x - 50, mys.y - 50);
}