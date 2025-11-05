#include "Zombici.h"

//Inicializace promìnných
Zombici::Zombici() {
	this->max_pocet_zombiku = 10;
	this->pocet_zombiku = 0;
	this->zombici = new Zombi[this->max_pocet_zombiku];
	this->odpocet = 0;
	this->zabitych_zombiku = 0;
	this->text.nastaveniTextu("Dosis-Light", 32, sf::Color::Magenta);

	for (int i = 0; i < 10; i++) {
		this->souradnice[i].x = -10000;
		this->souradnice[i].y = 10000;
	}
}

//Funkce která vykresluje objekty na obrazovku
void Zombici::render(sf::RenderTarget* okno) {
	for (int i = 0; i < this->max_pocet_zombiku; i++) {
		if (this->zombici[i].zije) {
			this->zombici[i].render(okno);
		}
	}
	this->text.render(okno);
}

//Funkce která aktualizuje informace o zombících a když je volno spawne nového
void Zombici::update(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac) {
	if (this->pocet_zombiku < this->max_pocet_zombiku) {
		if (this->odpocet == 25) {
			this->spawn(pozadi, kameny, dreva, hrac);
			this->odpocet = 0;
		}
		this->odpocet++;
	}

	for (int i = 0; i < this->max_pocet_zombiku; i++) {
		if (this->zombici[i].zije) {
			this->zombici[i].update(pozadi, kameny, dreva, hrac);
		}
	}
}

//Funkce která pohne se všemi zombíky když se pohne hráè
void Zombici::pohypProHrace(float x, float y) {
	for (int i = 0; i < this->max_pocet_zombiku; i++) {
		if (this->zombici[i].zije) {
			this->zombici[i].pohybProHrace(x, y);
		}
	}
}

//Funkce která spawnuje zombíky na mapì
void Zombici::spawn(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac) {
	for (int i = 0; i < this->max_pocet_zombiku; i++) {
		if (!this->zombici[i].zije) {
			this->zombici[i].spawn(pozadi, kameny, dreva, hrac, i, this->souradnice);

			this->pocet_zombiku++;
			break;
		}
	}
}

//Funkce která kontroluje, zda nìkterý ze zombíkù nebyl zastøelen
bool Zombici::kontrolaProStrelu(sf::Vector2f souradnice) {
	for (int i = 0; i < this->max_pocet_zombiku; i++) {
		if (this->zombici[i].zombi.vypln.getGlobalBounds().contains(souradnice) && this->zombici[i].zije) {
			this->zombici[i].zije = false;
			this->pocet_zombiku--;
			this->zabitych_zombiku++;
			return true;
		}
	}
	return false;
}