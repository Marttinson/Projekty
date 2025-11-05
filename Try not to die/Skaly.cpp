#include "Skaly.h"

//Inicializace promìnných
Skaly::Skaly() {
	this->prvek = new Skala[1];
	this->pocet_prvku = 0;
	this->velikost_pole = 1;
}

//Funkce která zvìtší dynamicky alokované pole, když dojde k jeho naplnìní
void Skaly::zvetseniPole() {
	int* souradniceX = new int[this->pocet_prvku];
	int* souradniceY = new int[this->pocet_prvku];
	for (int i = 0; i < this->pocet_prvku; i++) {
		souradniceX[i] = this->prvek[i].getPos().x;
		souradniceY[i] = this->prvek[i].getPos().y;
	}

	delete[] this->prvek;
	this->velikost_pole *= 2;
	this->prvek = new Skala[this->velikost_pole];
	for (int i = 0; i < this->pocet_prvku; i++) {
		this->prvek[i].nastaveniSkaly();
		this->prvek[i].setPos(souradniceX[i], souradniceY[i]);
		this->prvek[i].hp = 4;
	}
	delete[] souradniceX;
	delete[] souradniceY;
}

//Funkce která vrátí hodnotu, zda je pozice kam má být døevo umístìno volná nebo ne
bool Skaly::kontrola(sf::Vector2f souradnice) {
	for (int j = 0; j < this->pocet_prvku; j++) {
		if (souradnice.x - this->prvek[j].getGlobalBounds().x < -1540)
			return false;
		if (souradnice.y - this->prvek[j].getGlobalBounds().y < -1960)
			return false;
		if (souradnice.x + this->prvek[j].getGlobalBounds().x > 3460)
			return false;
		if (souradnice.y + this->prvek[j].getGlobalBounds().y > 3040)
			return false;
		if (this->prvek[j].vypln.getGlobalBounds().contains(souradnice) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x + this->prvek[j].getGlobalBounds().x, souradnice.y + this->prvek[j].getGlobalBounds().y) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x, souradnice.y + this->prvek[j].getGlobalBounds().y) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x + this->prvek[j].getGlobalBounds().x, souradnice.y) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x + this->prvek[j].getGlobalBounds().x / 2, souradnice.y) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x + this->prvek[j].getGlobalBounds().x / 2, souradnice.y + this->prvek[j].getGlobalBounds().y) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x, souradnice.y + this->prvek[j].getGlobalBounds().y / 2) ||
			this->prvek[j].vypln.getGlobalBounds().contains(souradnice.x + this->prvek[j].getGlobalBounds().x, souradnice.y + this->prvek[j].getGlobalBounds().x / 2)
			) {
			return false;
		}
	}
	return true;
}

//Funkce která pøidá prvek do pole
void Skaly::pridatPrvek(sf::Vector2f souradnice) {
	if (this->kontrola(souradnice)) {
		if (this->pocet_prvku == this->velikost_pole)
			this->zvetseniPole();

		this->prvek[this->pocet_prvku].umisteni(souradnice);
		this->prvek[this->pocet_prvku].hp = 4;
		this->pocet_prvku++;
	}
}

//Funkce která pohybuje se všemi prvky když se pohne hráè
void Skaly::pohyb(float x, float y) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		this->prvek[i].pohyb(x, y);
	}
}

//Vykresluje jednotlivé prvky na obrazovku
void Skaly::render(sf::RenderTarget* okno) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		this->prvek[i].render(okno);
	}
}