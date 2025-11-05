#include "Drevo.h"

//Inicualizace promìnných
Drevo::Drevo() {
	this->nastaveniDreva();
	this->hp = 5;
}

//Umístí døevo na zvolené souøadnice
void Drevo::umisteni(sf::Vector2f mys) {
	this->setPos(mys.x - 50, mys.y - 50);
}