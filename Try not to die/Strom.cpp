#include "Strom.h"

//Umístí strom na požadované souøadnice
void Strom::umisteni(sf::Vector2f souradnice) {
	this->nastaveniStromu();
	this->setPos(souradnice.x, souradnice.y);
}