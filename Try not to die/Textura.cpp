#include "Textura.h"

//Inicializace promìnné hp
Textura::Textura() {
	this->hp = 0;
}

//Nastavení obrázku podle zadané cesty
void Textura::nastaveniObrazku(std::string cesta) {
	this->obrazek.loadFromFile(cesta);
	this->textura.loadFromImage(this->obrazek);
	this->vypln.setTexture(this->textura);
}

//Nastavení obrázku trávy na pozadí
void Textura::nastaveniTravy() {
	this->nastaveniObrazku("Textury/Trava.png");
	this->obsah = "Trava";
}

//Nastavení obrázku vody na pozadí
void Textura::nastaveniVody() {
	this->nastaveniObrazku("Textury/Voda.png");
	this->obsah = "Voda";
}

//Nastavení obrázku skály
void Textura::nastaveniSkaly() {
	this->nastaveniObrazku("Textury/Skala.png");
	this->obsah = "Skala";
}

//Nastavení obrázku na zbytek který zbyde po skále
void Textura::nastaveniZbytkuPoSkale() {
	this->nastaveniObrazku("Textury/Zbytek_po_skale.png");
	this->obsah = "Zybet_po_skale";
}

//Nastavení obrázku stromu
void Textura::nastaveniStromu() {
	this->nastaveniObrazku("Textury/Strom.png");
	this->obsah = "Strom";
}

//Nastavení obrázku paøezu
void Textura::nastaveniParezu() {
	this->nastaveniObrazku("Textury/Parez.png");
	this->obsah = "Parez";
}

//Nastavení obrázku døeva
void Textura::nastaveniDreva() {
	this->nastaveniObrazku("Textury/Drevo_textura.png");
	this->obsah = "Drevo";
}

//Nastavení obrázku kamene
void Textura::nastaveniKamene() {
	this->nastaveniObrazku("Textury/Kamen_textura.png");
	this->obsah = "Kamen";
}

//Nastavení obrázku pistole pøi støelbì
void Textura::nastaveniStrelby() {
	this->nastaveniObrazku("Hrac/Strelba.png");
	this->obsah = "Strelba";
}

//Nastavení obrázku støely
void Textura::nastaveniStrely() {
	this->nastaveniObrazku("Hrac/Strela.png");
	this->obsah = "Strela";
}

//Vykreslení obrázku
void Textura::render(sf::RenderTarget* okno) {
	okno->draw(this->vypln);
}

//Funkce která pohybuje obrázkem když se pohybuje hráè
void Textura::pohyb(float x, float y) {
	float _x = this->vypln.getPosition().x + x;
	float _y = this->vypln.getPosition().y + y;
	this->vypln.setPosition(_x, _y);
}

//----------------------------------------------------------------------

//Funkce která nastaví souøadnice obrázku
void Textura::setPos(float x, float y) {
	this->vypln.setPosition(x, y);
}

//Funkce která nastaví o kolik stupòù se má obrázek natoèit
void Textura::setRotate(double uhel) {
	float a = (float)uhel;
	this->vypln.setRotation(a);
}

//Funkce která vrací šíøku obrázku
sf::Vector2f Textura::getGlobalBounds() {
	sf::Vector2f navratova_hodnota(this->vypln.getGlobalBounds().width, this->vypln.getGlobalBounds().height);
	return navratova_hodnota;
}

//Funkce která vrací pozici obrázku
sf::Vector2f Textura::getPos() {
	return this->vypln.getPosition();
}