#include "Menu.h"

//Inicializace pozadi a nadpisu
Menu::Menu() {
	this->pozadi.nastaveniObrazku("Menu/Pozadi.jpg");
	this->nadpis.nastaveniTextu("Melted_Monster", 100, sf::Color::Red, "Try not to Die");
}

//Vykreslení pozadí, nadpisu a tlaèítek
void Menu::render(sf::RenderTarget* okno) {
	this->pozadi.render(okno);

	this->nadpis.render(okno);
	this->nova_hra.render(okno);
	this->konec.render(okno);
}

//Nastavení tlaèítek
void Menu::nastaveni(sf::Vector2f rozliseni) {
	this->nadpis.text.setPosition(rozliseni.x / 2 - this->nadpis.text.getGlobalBounds().width / 2, rozliseni.y / 2 - 250);

	this->nova_hra.nastaveni("Zacit hru", 400, 75,
		sf::Color::Black, sf::Color(20, 20, 20), sf::Color(210, 210, 210),
		sf::Color(240, 240, 240), sf::Color::White, sf::Color(60, 60, 60));

	this->nova_hra.tvar.setPosition(rozliseni.x / 2 - this->nova_hra.tvar.getGlobalBounds().width / 2, rozliseni.y / 2);
	this->nova_hra.text.nastaveniTextu("HelpMe", 40, "Zacit hru");
	this->nova_hra.text.setPosition(this->nova_hra.tvar);

	this->konec.nastaveni("Konec", 400, 75,
		sf::Color::Black, sf::Color(20, 20, 20), sf::Color(210, 210, 210),
		sf::Color(240, 240, 240), sf::Color::White, sf::Color(60, 60, 60));

	this->konec.tvar.setPosition(rozliseni.x / 2 - this->konec.tvar.getGlobalBounds().width / 2,
		this->nova_hra.tvar.getPosition().y + this->nova_hra.tvar.getGlobalBounds().height + 100);

	this->konec.text.nastaveniTextu("HelpMe", 40, "Konec");
	this->konec.text.setPosition(this->konec.tvar);
}

//Funkce která aktualizuje stav tlaèítek
void Menu::update(sf::Vector2f pozice_kurzoru) {
	this->nova_hra.update(pozice_kurzoru);
	this->konec.update(pozice_kurzoru);
}