#include "Inventar.h"

//Inicializace promìnných
Inventar::Inventar() {
	this->pocet = 0;
	this->poradi = 0;

	this->txt_pocet.nastaveniTextu("Roboto-Black", 20, sf::Color::Red);
	this->txt_poradi.nastaveniTextu("Roboto-Black", 20, sf::Color::Red);
}

//Nastavení hodnot podle parametrù funkce
void Inventar::zalozeniInv(int poradi, std::string cesta, float x, float y, bool je_tak) {
	this->poradi = poradi;
	this->txt_poradi.setString(std::to_string(poradi));
	if(je_tak)
		this->txt_pocet.setString(std::to_string(this->pocet));

	this->nastaveniObrazku(cesta);
	this->vypln.setPosition(x, y);
	this->txt_pocet.text.setPosition(x + 25 - this->txt_pocet.text.getGlobalBounds().width / 2,
		y + this->vypln.getGlobalBounds().height - this->txt_pocet.text.getGlobalBounds().height - 6);

	this->txt_poradi.text.setPosition(x + 1, y + 1);
}

//Aktualizace textu, který vypisuje poèet prvkù
void Inventar::setPocet(int pocet) {
	this->txt_pocet.setString(std::to_string(pocet));
}

//Vykresluje text a obrázek
void Inventar::render(sf::RenderTarget* okno) {
	okno->draw(this->vypln);
	this->txt_pocet.render(okno);
	this->txt_poradi.render(okno);
}