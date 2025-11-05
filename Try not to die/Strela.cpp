#include "Strela.h"

//Inicializace promìnných
Strela::Strela() {
	this->vystreleno = false;
	this->zvuk.nastaveni("Zvuk_strelby", 15);
}

//Vykreslení støely
void Strela::render(sf::RenderTarget* okno) {
	if (this->vystreleno) {
		this->strela.render(okno);
	}
}

//Funkce která aktualizuje hodnoty a stav støely
void Strela::update(sf::Clock cas) {
	if (this->vystreleno) {
		this->pohyb(cas);
	}
}

//Funkce která nastaví potøebné hodnoty støele, zavolá se po stisku levého tlaèítka na myši
void Strela::nastaveni(sf::Vector2f souradnice, float uhel, sf::Vector2f pozice_kurzoru) {
	this->zvuk.zvuk.play();
	this->strela.nastaveniObrazku("Hrac/Strela.png");
	this->strela.setPos(souradnice.x, souradnice.y);
	this->strela.setRotate(uhel);
	this->vystreleno = true;

	this->cil = pozice_kurzoru;

	this->posun.x = (this->cil.x - this->strela.getPos().x) / 10;
	this->posun.y = (this->cil.y - this->strela.getPos().y) / 10;
}

//Funkce která pohybuje se støelou když se pohybuje hráè
void Strela::pohybProHrace(float x, float y) {
	float _x = this->strela.getPos().x + x;
	float _y = this->strela.getPos().y + y;
	this->strela.vypln.setPosition(_x, _y);
}

//Funkce která umožòuje støele pohyb
void Strela::pohyb(sf::Clock cas) {
	if ((int)floor(cas.getElapsedTime().asMilliseconds()) % 2 == 0) {
		if (this->strela.vypln.getRotation() <= 90) {
			if (this->strela.getPos().x < this->cil.x && this->strela.getPos().y < this->cil.y) {
				this->strela.pohyb(this->posun.x, this->posun.y);
			}
			else {
				this->vystreleno = false;
			}
		}
		else if (this->strela.vypln.getRotation() > 90 && this->strela.vypln.getRotation() <= 180) {
			if (this->strela.getPos().x > this->cil.x && this->strela.getPos().y < this->cil.y) {
				this->strela.pohyb(this->posun.x, this->posun.y);
			}
			else {
				this->vystreleno = false;
			}
		}
		else if (this->strela.vypln.getRotation() > 180 && this->strela.vypln.getRotation() <= 270) {
			if (this->strela.getPos().x > this->cil.x && this->strela.getPos().y > this->cil.y) {
				this->strela.pohyb(this->posun.x, this->posun.y);
			}
			else {
				this->vystreleno = false;
			}
		}
		else if (this->strela.vypln.getRotation() > 270 && this->strela.vypln.getRotation() <= 360) {
			if (this->strela.getPos().x < this->cil.x && this->strela.getPos().y > this->cil.y) {
				this->strela.pohyb(this->posun.x, this->posun.y);
			}
			else {
				this->vystreleno = false;
			}
		}
	}
}