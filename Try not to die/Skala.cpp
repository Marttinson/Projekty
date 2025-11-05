#include "Skala.h"

//Umístìní skály na požadované souøadnice
void Skala::umisteni(sf::Vector2f souradnice) {
	this->nastaveniSkaly();
	this->setPos(souradnice.x, souradnice.y);
}