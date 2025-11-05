#include "Dreva.h"

//Inicializace promìnných
Dreva::Dreva() {
	this->drevo = new Drevo[1];
	this->pocet_prvku = 0;
	this->velikost_pole = 1;
	this->pocet_dreva = 0;
	this->index = 0;
}

//Funkce která zvìtší dynamicky alokované pole, když dojde k jeho naplnìní
void Dreva::zvetseniPole() {
	int* souradniceX = new int[this->pocet_prvku];
	int* souradniceY = new int[this->pocet_prvku];
	int* hp = new int[this->pocet_prvku];
	for (int i = 0; i < this->pocet_prvku; i++) {
		souradniceX[i] = this->drevo[i].getPos().x;
		souradniceY[i] = this->drevo[i].getPos().y;
		hp[i] = this->drevo[i].hp;
	}

	delete[] this->drevo;
	this->velikost_pole *= 2;
	this->drevo = new Drevo[this->velikost_pole];
	for (int i = 0; i < this->pocet_prvku; i++) {
		this->drevo[i].nastaveniDreva();
		this->drevo[i].setPos(souradniceX[i], souradniceY[i]);
		this->drevo[i].hp = hp[i];
	}
	delete[] hp;
	delete[] souradniceX;
	delete[] souradniceY;
}

//Funkce která pøidá prvek do pole
void Dreva::pridatPrvek(sf::Vector2f mys) {
	if (this->pocet_prvku == this->velikost_pole)
		this->zvetseniPole();

	this->drevo[this->pocet_prvku].umisteni(mys);
	this->pocet_prvku++;
}

//Funkce která vrátí hodnotu, zda je pozice kam má být døevo umístìno volná nebo ne
bool Dreva::zkontrolovat(sf::Vector2f mys) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->drevo[i].vypln.getGlobalBounds().contains(mys) && this->drevo[i].hp > 0) {
			return false;
		}
		if (this->drevo[i].vypln.getGlobalBounds().contains(mys.x - 50, mys.y - 50) && this->drevo[i].hp > 0) {
			return false;
		}
		if (this->drevo[i].vypln.getGlobalBounds().contains(mys.x + 50, mys.y - 50) && this->drevo[i].hp > 0) {
			return false;
		}
		if (this->drevo[i].vypln.getGlobalBounds().contains(mys.x - 50, mys.y + 50) && this->drevo[i].hp > 0) {
			return false;
		}
		if (this->drevo[i].vypln.getGlobalBounds().contains(mys.x + 50, mys.y + 50) && this->drevo[i].hp > 0) {
			return false;
		}
	}

	return true;
}

//Kontroluje zda se zadané souøadnice pøekrývají s nìjakým z prvkù a tuto hodnotu vrací
bool Dreva::kontrolaPrekryti(float x, float y) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->drevo[i].vypln.getGlobalBounds().contains(x, y) && this->drevo[i].hp > 0) {
			this->index = i;
			return true;
		}
	}
	return false;
}

//Kontroluje zda se zadané souøadnice pøekrývají s nìjakým z prvkù a tuto hodnotu vrací
bool Dreva::kontrolaPrekryti(sf::Vector2f souradnice) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->drevo[i].vypln.getGlobalBounds().contains(souradnice) && this->drevo[i].hp > 0)
			return true;
	}
	return false;
}

//Funkce která pohybuje se všemi prvky když se pohne hráè
void Dreva::pohyb(float x, float y) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->drevo[i].hp > 0)
			this->drevo[i].pohyb(x, y);
	}
}

//Vykresluje jednotlivé prvky na obrazovku
void Dreva::render(sf::RenderTarget* okno) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->drevo[i].hp > 0)
			this->drevo[i].render(okno);
	}
}