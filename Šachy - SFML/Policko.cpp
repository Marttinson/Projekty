#include "Policko.h"

Policko::Policko() {
	this->tvar.setSize(sf::Vector2f(50, 50));
	this->tvar.setFillColor(sf::Color::Blue);

	this->zmacknuto = false;
	this->pravy_zmacknuto = false;
	this->barva = "";
	this->pindaJednou = true;

	//this->nastaveniText();
}

Policko::~Policko() {

}

void Policko::render(sf::RenderTarget* target) {
	target->draw(this->tvar);
	//target->draw(this->text);
	target->draw(this->vypln);
}

void Policko::nastaveniFont() {
	if (!this->font.loadFromFile("Fonts/Roboto-Black.ttf")) {
		std::cout << "ERROR::INITFONT::Failde to load font!" << std::endl;
	}
}

void Policko::nastaveniText() {
	this->nastaveniFont();
	this->text.setFont(this->font);
	this->text.setCharacterSize(18);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("");
}

void Policko::nastaveniObrazku(std::string cesta, std::string figurka) {
	this->obrazek.loadFromFile(cesta);
	this->textura.loadFromImage(this->obrazek);
	this->vypln.setTexture(textura);
	this->vypln.setPosition(this->tvar.getPosition());
	this->figurka = figurka;
}

void Policko::nastaveniObrazku(std::string cesta, std::string figurka, std::string barva) {
	this->obrazek.loadFromFile(cesta);
	this->textura.loadFromImage(this->obrazek);
	this->vypln.setTexture(textura);
	this->vypln.setPosition(this->tvar.getPosition());
	this->figurka = figurka;
	this->barva = barva;
}

void Policko::nastaveniObrazku(Policko policko) {
	this->vypln.setTexture(*policko.vypln.getTexture());
	this->vypln.setPosition(this->tvar.getPosition());
	this->figurka = policko.figurka;
	this->barva = policko.barva;
	this->pindaJednou = policko.pindaJednou;
}

void Policko::setText(std::string text) {
	this->text.setString(text);
	this->text.setPosition(sf::Vector2f(
		this->tvar.getPosition().x + this->tvar.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->tvar.getPosition().y + this->tvar.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height));
}

void Policko::setSouradnice(float x, float y) {
	this->tvar.setPosition(sf::Vector2f(x, y));
}

void Policko::setBarvaTextu(sf::Color barva) {
	this->text.setFillColor(barva);
}

void Policko::setVelikost(float x, float y) {
	this->tvar.setSize(sf::Vector2f(x, y));
}

void Policko::setBarvuPozadi(sf::Color barva) {
	this->tvar.setFillColor(barva);
}

std::string Policko::getText() {
	return this->text.getString();
}

sf::Color Policko::getBarvaTextu() {
	return this->text.getFillColor();
}