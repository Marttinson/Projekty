#include "Esc.h"

//Inicializace tlaèítek a pozadí
void Esc::nastaveni(sf::Vector2f rozliseni) {
	this->pozadi.nastaveniObrazku("Menu/ESC.png");
	this->pozadi.setPos(rozliseni.x / 2 - this->pozadi.getGlobalBounds().x / 2, rozliseni.y / 2 - this->pozadi.getGlobalBounds().y / 2);

	this->pokracovat.nastaveni("Pokracovat", 300, 75, 
		sf::Color::Black, sf::Color(20, 20, 20), sf::Color(210, 210, 210), sf::Color(240, 240, 240), sf::Color::White, sf::Color(60, 60, 60));
	this->pokracovat.tvar.setPosition(this->pozadi.getPos().x + 50, this->pozadi.getPos().y + 100);
	this->pokracovat.text.nastaveniTextu("HelpMe", 32, "Pokracovat");
	this->pokracovat.text.setPosition(this->pokracovat.tvar);

	this->konec.nastaveni("Konec", 300, 75, 
		sf::Color::Black, sf::Color(20, 20, 20), sf::Color(210, 210, 210), sf::Color(240, 240, 240), sf::Color::White, sf::Color(60, 60, 60));
	this->konec.tvar.setPosition(this->pozadi.getPos().x + 50,
		this->pozadi.getPos().y + this->pozadi.getGlobalBounds().y - this->konec.tvar.getGlobalBounds().height - 100);
	this->konec.text.nastaveniTextu("HelpMe", 32, "Konec");
	this->konec.text.setPosition(this->konec.tvar);
}

//Funkce která aktualizuje stav tlaèítek
void Esc::update(sf::Vector2f pozice_kurzoru) {
	this->pokracovat.update(pozice_kurzoru);
	this->konec.update(pozice_kurzoru);
}

//Vykreslení tlaèítek a pozadí
void Esc::render(sf::RenderTarget* okno) {
	this->pozadi.render(okno);
	this->pokracovat.render(okno);
	this->konec.render(okno);
}