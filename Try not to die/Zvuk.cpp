#include "Zvuk.h"

//Nastaví zvuk pomocí jeho cesty a hlasitosti
void Zvuk::nastaveni(std::string cesta, int hlasitost) {
	if (!this->buffer.loadFromFile("Zvuky/" + cesta + ".ogg"))
	{
		std::cout << "Error " + cesta << std::endl;
	}
	this->zvuk.setBuffer(this->buffer);
	this->zvuk.setVolume(hlasitost);
}