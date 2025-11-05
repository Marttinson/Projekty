#include "Strelba.h"

//Inicializace promìnných
Strelba::Strelba() {
	this->zasobnik = 10;
	this->strely = new Strela[this->zasobnik];
	this->pocet_strel = 0;
	this->pauza = 20;
}

//Vykreslení støel na obrazovku
void Strelba::render(sf::RenderTarget* okno) {
	for (int i = 0; i < this->zasobnik; i++) {
		this->strely[i].render(okno);
	}
}

//Funkce která aktualizuje informace o støelách, jestli do nìèeho nevrazily, pohyb, ...
void Strelba::update(sf::Clock cas, Dreva dreva, Kameny kameny, Pozadi pozadi, Zombici& zombici, Hrac* hrac) {
	for (int i = 0; i < this->zasobnik; i++) {
		if (this->strely[i].vystreleno) {
			if (dreva.kontrolaPrekryti(this->strely[i].strela.getPos()))
				this->strely[i].vystreleno = false;
			if (kameny.kontrolaPrekryti(this->strely[i].strela.getPos()))
				this->strely[i].vystreleno = false;
			if (pozadi.jeTamStrom(this->strely[i].strela.getPos().x, this->strely[i].strela.getPos().y))
				this->strely[i].vystreleno = false;
			if (pozadi.jeTamSkala(this->strely[i].strela.getPos().x, this->strely[i].strela.getPos().y) && !hrac->na_skale)
				this->strely[i].vystreleno = false;
			if (zombici.kontrolaProStrelu(sf::Vector2f(this->strely[i].strela.getPos().x + this->strely[i].strela.getGlobalBounds().x, this->strely[i].strela.getPos().y)))
				this->strely[i].vystreleno = false;
		}
	}

	for (int i = 0; i < this->zasobnik; i++) {
		this->strely[i].update(cas);
	}

	this->pocet_strel = 0;
	for (int i = 0; i < this->zasobnik; i++) {
		if (this->strely[i].vystreleno)
			this->pocet_strel++;
	}
}

//Funkce která se zavolá po stisku levého tlaèítka na myši a tím se pøidá a vykreslí støela
void Strelba::pridat(sf::Vector2f souradnice, float uhel, sf::Vector2f pozice_kurzoru) {
	if (this->pauza == 25) {
		for (int i = 0; i < this->zasobnik; i++) {
			if (!this->strely[i].vystreleno) {
				this->strely[i].nastaveni(souradnice, uhel, pozice_kurzoru);
				break;
			}
		}
		this->pauza = 0;
	}
	else
		this->pauza++;
}

//Funkce která pohybuje se støelama když se pohybuje hráè
void Strelba::pohypProHrace(float x, float y) {
	for (int i = 0; i < this->zasobnik; i++) {
		if (this->strely[i].vystreleno) {
			this->strely[i].pohybProHrace(x, y);
		}
	}
}