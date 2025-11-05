#include "Text.h"

//Vykresluje text na obrazovku
void Text::render(sf::RenderTarget* okno) {
	okno->draw(this->text);
}

//Nastaví zvolený font
void Text::nastaveniFontu(std::string font) {
	if (!this->font.loadFromFile("Fonts/" + font + ".ttf")) {
		std::cout << "ERROR::INITFONT::Failde to load font!" << std::endl;
	}
}

//Nastaví text pomocí fontu, velikosti a jeho obsahu
void Text::nastaveniTextu(std::string font, int velikost, std::string text) {
	this->nastaveniFontu(font);
	this->text.setFont(this->font);
	this->text.setCharacterSize(velikost);
	this->text.setString(text);
}

//Nastaví text pomocí fontu, velikost a barvy
void Text::nastaveniTextu(std::string font, int velikost, sf::Color barva) {
	this->nastaveniFontu(font);
	this->text.setFont(this->font);
	this->text.setCharacterSize(velikost);
	this->text.setFillColor(barva);
	this->text.setString("");
}

//Nastaví text pomocí fontu, velikosti, barvy a obsahu
void Text::nastaveniTextu(std::string font, int velikost, sf::Color barva, std::string text) {
	this->nastaveniFontu(font);
	this->text.setFont(this->font);
	this->text.setCharacterSize(velikost);
	this->text.setFillColor(barva);
	this->text.setString(text);
}

//Funkce která nastaví obsah textu
void Text::setString(std::string text) {
	this->text.setString(text);
}

//Funkce která nastaví souøadnice textu
void Text::setPosition(sf::RectangleShape tvar) {
	this->text.setPosition(tvar.getPosition().x + tvar.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
		tvar.getPosition().y + tvar.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
}