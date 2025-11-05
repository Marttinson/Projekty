#include "Kameny.h"

//Inicializace promìnných
Kameny::Kameny() {
	this->kamen = new Kamen[1];
	this->pocet_prvku = 0;
	this->velikost_pole = 1;
	this->pocet_kamene = 0;
	this->index = NULL;
}

//Funkce která zvìtší dynamicky alokované pole, když dojde k jeho naplnìní
void Kameny::zvetseniPole() {
	int* souradniceX = new int[this->pocet_prvku];
	int* souradniceY = new int[this->pocet_prvku];
	int* hp = new int[this->pocet_prvku];
	for (int i = 0; i < this->pocet_prvku; i++) {
		souradniceX[i] = this->kamen[i].getPos().x;
		souradniceY[i] = this->kamen[i].getPos().y;
		hp[i] = this->kamen[i].hp;
	}

	delete[] this->kamen;
	this->velikost_pole *= 2;
	this->kamen = new Kamen[this->velikost_pole];
	for (int i = 0; i < this->pocet_prvku; i++) {
		this->kamen[i].nastaveniKamene();
		this->kamen[i].setPos(souradniceX[i], souradniceY[i]);
		this->kamen[i].hp = hp[i];
	}
	delete[] hp;
	delete[] souradniceX;
	delete[] souradniceY;
}

//Funkce která pøidá prvek do pole
void Kameny::pridatPrvek(sf::Vector2f mys) {
	if (this->pocet_prvku == this->velikost_pole)
		this->zvetseniPole();

	this->kamen[this->pocet_prvku].umisteni(mys);
	this->pocet_prvku++;
}

//Funkce která vrátí hodnotu, zda je pozice kam má být kámen umístìn volná nebo ne
bool Kameny::zkontrolovat(sf::Vector2f mys) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->kamen[i].vypln.getGlobalBounds().contains(mys) && this->kamen[i].hp > 0) {
			return false;
		}
		if (this->kamen[i].vypln.getGlobalBounds().contains(mys.x - 50, mys.y - 50) && this->kamen[i].hp > 0) {
			return false;
		}
		if (this->kamen[i].vypln.getGlobalBounds().contains(mys.x + 50, mys.y - 50) && this->kamen[i].hp > 0) {
			return false;
		}
		if (this->kamen[i].vypln.getGlobalBounds().contains(mys.x - 50, mys.y + 50) && this->kamen[i].hp > 0) {
			return false;
		}
		if (this->kamen[i].vypln.getGlobalBounds().contains(mys.x + 50, mys.y + 50) && this->kamen[i].hp > 0) {
			return false;
		}
	}
	return true;
}

//Kontroluje zda se zadané souøadnice pøekrývají s nìjakým z prvkù a tuto hodnotu vrací
bool Kameny::kontrolaPrekryti(float x, float y) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->kamen[i].vypln.getGlobalBounds().contains(x, y) && this->kamen[i].hp > 0) {
			this->index = i;
			return true;
		}
	}
	return false;
}

//Kontroluje zda se zadané souøadnice pøekrývají s nìjakým z prvkù a tuto hodnotu vrací
bool Kameny::kontrolaPrekryti(sf::Vector2f souradnice) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if (this->kamen[i].vypln.getGlobalBounds().contains(souradnice) && this->kamen[i].hp > 0) {
			return true;
		}
	}
	return false;
}

//Funkce která pohybuje se všemi prvky když se pohne hráè
void Kameny::pohyb(float x, float y) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if(this->kamen[i].hp > 0)
			this->kamen[i].pohyb(x, y);
	}
}

//Vykresluje jednotlivé prvky na obrazovku
void Kameny::render(sf::RenderTarget* okno) {
	for (int i = 0; i < this->pocet_prvku; i++) {
		if(this->kamen[i].hp > 0)
			this->kamen[i].render(okno);
	}
}