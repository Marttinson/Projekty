#include "Tlacitko.h"

Tlacitko::Tlacitko() {
	this->tvar.setSize(sf::Vector2f(50, 50));
	this->tvar.setFillColor(sf::Color::Blue);

	this->zmacknuto = false;
	this->pravy_zmacknuto = false;

	this->nastaveniText();
}

Tlacitko::~Tlacitko() {

}

void Tlacitko::update(sf::Vector2f pozice_kurzoru) {
	if (this->tvar.getGlobalBounds().contains(pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->zmacknuto) {
		if (this->tvar.getFillColor() == sf::Color::Blue) {
			this->tvar.setFillColor(sf::Color::Yellow);
		}
		else {
			this->tvar.setFillColor(sf::Color::Blue);
		}
		this->zmacknuto = true;
	}
	else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		this->zmacknuto = false;
	}
}

void Tlacitko::render(sf::RenderTarget* target) {
	target->draw(this->tvar);
	target->draw(this->text);
}

void Tlacitko::nastaveniFont() {
	if (!this->font.loadFromFile("Fonts/Roboto-Black.ttf")) {
		std::cout << "ERROR::INITFONT::Failde to load font!" << std::endl;
	}
}

void Tlacitko::nastaveniText() {
	this->nastaveniFont();
	this->text.setFont(this->font);
	this->text.setCharacterSize(18);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("");
}

void Tlacitko::setText(std::string text) {
	this->text.setString(text);
	this->text.setPosition(sf::Vector2f(
		this->tvar.getPosition().x + this->tvar.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->tvar.getPosition().y + this->tvar.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height));
}

void Tlacitko::setSouradnice(float x, float y) {
	this->tvar.setPosition(sf::Vector2f(x, y));
}

void Tlacitko::setBarvaTextu(sf::Color barva) {
	this->text.setFillColor(barva);
}

void Tlacitko::setVelikost(float x, float y) {
	this->tvar.setSize(sf::Vector2f(x, y));
}

void Tlacitko::setBarvuPozadi(sf::Color barva) {
	this->tvar.setFillColor(barva);
}

std::string Tlacitko::getText() {
	return this->text.getString();
}

sf::Color Tlacitko::getBarvaTextu() {
	return this->text.getFillColor();
}