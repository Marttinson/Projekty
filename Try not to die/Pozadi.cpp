#include "Pozadi.h"

//Funkce která naplní pozadí trávou, vodou, kameny a stromy
void Pozadi::naplnPozadi(sf::Vector2f rozliseni, Hrac* hrac) {
	this->velikost_hraci_plochy = 35;
	this->pocet_stromu = 120;
	this->pocet_skal = 20;

	this->prvek = new Textura * [35];

	for (int i = 0; i < 5; i++) {
		this->prvek[i] = new Textura[35];
		for (int j = 0; j < this->velikost_hraci_plochy; j++) {
			this->prvek[i][j].nastaveniVody();
		}
	}
	for (int i = 5; i < 30; i++) {
		this->prvek[i] = new Textura[35];
		for (int j = 0; j < 5; j++) {
			this->prvek[i][j].nastaveniVody();
		}
		for (int j = 5; j < 30; j++) {
			this->prvek[i][j].nastaveniTravy();
		}
		for (int j = 30; j < this->velikost_hraci_plochy; j++) {
			this->prvek[i][j].nastaveniVody();
		}
	}
	for (int i = 30; i < this->velikost_hraci_plochy; i++) {
		this->prvek[i] = new Textura[35];
		for (int j = 0; j < this->velikost_hraci_plochy; j++) {
			this->prvek[i][j].nastaveniVody();
		}
	}

	float x = -3500 + rozliseni.x / 2; //7000 -> 5000 trava
	float y = -3500 + rozliseni.y / 2; //7000 -> 5000 trava
	for (int i = 0; i < this->velikost_hraci_plochy; i++) {
		for (int j = 0; j < this->velikost_hraci_plochy; j++) {
			this->prvek[i][j].setPos(x, y);
			x += 200;
		}
		x = -3500 + rozliseni.x / 2;
		y += 200;
	}

	srand(time(0));
	//kameny
	for (int i = 0; i < this->pocet_skal; i++) {
		float randomX = (rand() % 4800) + this->prvek[5][5].getPos().x;
		float randomY = (rand() % 4800) + this->prvek[5][5].getPos().y;

		this->skaly.pridatPrvek(sf::Vector2f(randomX, randomY));
	}

	//stromy
	for (int i = 0; i < this->pocet_stromu; i++) {
		float randomX = (rand() % 4800) + this->prvek[5][5].getPos().x;
		float randomY = (rand() % 4800) + this->prvek[5][5].getPos().y;

		Strom velikost;
		velikost.nastaveniStromu();
		bool prekryti = false;
		for (int j = 0; j < this->skaly.pocet_prvku; j++) {
			if (this->skaly.prvek[j].vypln.getGlobalBounds().contains(randomX, randomY) ||
				this->skaly.prvek[j].vypln.getGlobalBounds().contains(randomX + velikost.getGlobalBounds().x, randomY) ||
				this->skaly.prvek[j].vypln.getGlobalBounds().contains(randomX, randomY + velikost.getGlobalBounds().y) ||
				this->skaly.prvek[j].vypln.getGlobalBounds().contains(randomX + velikost.getGlobalBounds().x, randomY + velikost.getGlobalBounds().y)
				) {
				prekryti = true;
				break;
			}
		}

		if (!prekryti)
			this->stromy.pridatPrvek(sf::Vector2f(randomX, randomY));
	}
}

//Vykreslení pozadí
void Pozadi::renderPozadi(sf::RenderTarget* okno) {
	for (int i = 0; i < this->velikost_hraci_plochy; i++) {
		for (int j = 0; j < this->velikost_hraci_plochy; j++) {
			this->prvek[i][j].render(okno);
		}
	}
	this->stromy.render(okno);
	this->skaly.render(okno);
}

//Funkce která pohybuje pozadím když se pohybuje hráè
void Pozadi::pohyb(float x, float y) {
	for (int i = 0; i < this->velikost_hraci_plochy; i++) {
		for (int j = 0; j < velikost_hraci_plochy; j++) {
			this->prvek[i][j].pohyb(x, y);
		}
	}
}

//Funkce která vrátí textový øetìzec jehož obsahem je obsah na zadaných souøadnicích
std::string Pozadi::pozadiNaSouradnici(float souradniceX, float souradniceY) {
	for (int i = 0; i < this->velikost_hraci_plochy; i++) {
		for (int j = 0; j < this->velikost_hraci_plochy; j++) {
			if (this->prvek[i][j].vypln.getGlobalBounds().contains(souradniceX, souradniceY)) {
				return this->prvek[i][j].obsah;
			}
		}
	}
	return "nic";
}

//Funkce která vrátí true pokud je na zadaných souøadnicích strom a false pokud tam není
bool Pozadi::jeTamStrom(float souradniceX, float souradniceY) {
	for (int i = 0; i < this->stromy.pocet_prvku; i++) {
		if (this->stromy.prvek[i].vypln.getGlobalBounds().contains(souradniceX, souradniceY) && this->stromy.prvek[i].obsah == "Strom")
			return true;
	}
	return false;
}

//Funkce která vrátí true pokud je na zadaných souøadnicích skála a false pokud tam není
bool Pozadi::jeTamSkala(float souradniceX, float souradniceY) {
	for (int i = 0; i < this->skaly.pocet_prvku; i++) {
		if (this->skaly.prvek[i].vypln.getGlobalBounds().contains(souradniceX, souradniceY) && this->skaly.prvek[i].obsah == "Skala")
			return true;
	}
	return false;
}