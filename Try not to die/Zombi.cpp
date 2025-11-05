#include "Zombi.h"

//Inicializace promìnných
Zombi::Zombi() {
	this->zombi.nastaveniObrazku("Zombici/Zombi_do_prava1.png");
	this->smer = "Prava";
	this->pozice = 1;
	this->odpocet_pohybu = 0;
	this->zije = false;
	this->prava = true;
	this->leva = true;
	this->nahore = true;
	this->dole = true;
	this->strana = "";
	this->posun = 5;
	this->na_hit = false;
	this->hit_kamen = false;
	this->hit_drevo = false;
}

//Funkce která náhodnì vybere souøadnice a pokud je tam volno spawne na nich zombíka
void Zombi::spawn(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac, int index, sf::Vector2f* souradnice) {
	srand(time(0));
	this->zije = true;

	int randomX = 0;
	int randomY = 0;

	do {
		randomX = (rand() % 4800) + pozadi.prvek[5][5].getPos().x;
		randomY = (rand() % 4800) + pozadi.prvek[5][5].getPos().y;
	} while (!kontrolaProSpawn(pozadi, kameny, dreva, hrac, randomX, randomY, index, souradnice));

	this->zombi.setPos(randomX, randomY);
}

//Funkce která kontroluje zda je na vybraných souøadnicích volno
bool Zombi::kontrolaProSpawn(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac, int randomX, int randomY, int index, sf::Vector2f* souradnice) {
	//kontrola stromù pøi spawnu zombíka
	if (pozadi.jeTamStrom(randomX, randomY))
		return false;
	else if (pozadi.jeTamStrom(randomX, randomY + this->zombi.getGlobalBounds().y))
		return false;
	else if (pozadi.jeTamStrom(randomX + this->zombi.getGlobalBounds().x, randomY))
		return false;
	else if (pozadi.jeTamStrom(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y))
		return false;

	//kontrola skal pøi spawnu zombíka
	if (pozadi.jeTamSkala(randomX, randomY))
		return false;
	else if (pozadi.jeTamSkala(randomX, randomY + this->zombi.getGlobalBounds().y))
		return false;
	else if (pozadi.jeTamSkala(randomX + this->zombi.getGlobalBounds().x, randomY))
		return false;
	else if (pozadi.jeTamSkala(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y))
		return false;

	//kontrola døeva pøi spawnu zombíka
	for (int i = 0; i < dreva.pocet_prvku; i++) {
		if (dreva.drevo->vypln.getGlobalBounds().contains(randomX, randomY))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX, randomY + this->zombi.getGlobalBounds().y))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX, randomY + this->zombi.getGlobalBounds().y / 2))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX, randomY))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX, randomY + this->zombi.getGlobalBounds().y))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y / 2))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY))
			return false;
		else if (dreva.drevo->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y))
			return false;
	}

	//kontrola kamene pøi spawnu zombíka
	for (int i = 0; i < kameny.pocet_prvku; i++) {
		if (kameny.kamen->vypln.getGlobalBounds().contains(randomX, randomY))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX, randomY + this->zombi.getGlobalBounds().y))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX, randomY + this->zombi.getGlobalBounds().y / 2))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX, randomY))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX, randomY + this->zombi.getGlobalBounds().y))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y / 2))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY))
			return false;
		else if (kameny.kamen->vypln.getGlobalBounds().contains(randomX + this->zombi.getGlobalBounds().x, randomY + this->zombi.getGlobalBounds().y))
			return false;
	}

	//kontrola pro spawn zombíka u hráèe
	if (randomX > hrac->getPos().x - 500 - this->zombi.getGlobalBounds().x && randomX < hrac->getPos().x + hrac->getGlobalBounds().x + 500) {
		if (randomY > hrac->getPos().y - 500 - this->zombi.getGlobalBounds().y && randomX < hrac->getPos().y + hrac->getGlobalBounds().y + 500)
			return false;
	}

	//kontrola aby se zombici nespawnovali na sobì
	for (int i = 0; i < 25; i++) {
		if (randomX == souradnice[i].x && randomY == souradnice[i].y)
			return false;
	}

	souradnice[index].x = randomX;
	souradnice[index].y = randomY;

	return true;
}

//Funkce která zombíka vykresluje na obrazovku
void Zombi::render(sf::RenderTarget* okno) {
	this->zombi.render(okno);
}

//Funkce která aktualizuje stav zombíka
void Zombi::update(Pozadi pozadi, Kameny& kameny, Dreva& dreva, Hrac* hrac) {
	this->na_hit = false;
	if (hrac->vypln.getGlobalBounds().contains(this->zombi.getPos())) {
		this->na_hit = true;
	}
	else if (hrac->vypln.getGlobalBounds().contains(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y)) {
		this->na_hit = true;
	}
	else if (hrac->vypln.getGlobalBounds().contains(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		this->na_hit = true;
	}
	else if (hrac->vypln.getGlobalBounds().contains(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		this->na_hit = true;
	}

	if (this->odpocet_pohybu == 25) {
		if (this->smer == "Prava") {
			if (this->pozice == 2) {
				this->zombi.nastaveniObrazku("Zombici/Zombi_do_prava1.png");
				this->pozice = 1;
			}
			else {
				this->zombi.nastaveniObrazku("Zombici/Zombi_do_prava2.png");
				this->pozice = 2;
			}
		}
		else {
			if (this->pozice == 2) {
				this->zombi.nastaveniObrazku("Zombici/Zombi_do_leva1.png");
				this->pozice = 1;
			}
			else {
				this->zombi.nastaveniObrazku("Zombici/Zombi_do_leva2.png");
				this->pozice = 2;
			}
		}
		this->odpocet_pohybu = 0;

		if (this->na_hit) {
			hrac->hp -= 2;
		}

		if (this->hit_kamen) {
			kameny.kamen[this->index_prvku].hp--;
		}
		else if (this->hit_drevo) {
			dreva.drevo[this->index_prvku].hp--;
		}
	}
	this->kontrolaPohybu(pozadi, kameny, dreva, hrac);
	this->pohyb(hrac);

	this->odpocet_pohybu++;
}

//Funkce která pohybuje se zombíkem, když se pohne hráè
void Zombi::pohybProHrace(float x, float y) {
	float _x = this->zombi.getPos().x + x;
	float _y = this->zombi.getPos().y + y;
	this->zombi.vypln.setPosition(_x, _y);
}

//Funkce která kontroluje jakým smìrem se zombík mùže a jakým nemùže pohybovat
void Zombi::kontrolaPohybu(Pozadi pozadi, Kameny kameny, Dreva dreva, Hrac* hrac) {
	//stromy 
	bool stromy[] = {true, true, true, true};
	//levá strana
	if (pozadi.jeTamStrom(this->zombi.getPos().x, this->zombi.getPos().y + 10) && this->smer == "Leva") {
		stromy[0] = false;
	}
	else if (pozadi.jeTamStrom(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10) && this->smer == "Leva") {
		stromy[0] = false;
	}
	//pravá strana
	if (pozadi.jeTamStrom(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + 10) && this->smer == "Prava") {
		stromy[1] = false;
	}
	else if (pozadi.jeTamStrom(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10) && this->smer == "Prava") {
		stromy[1] = false;
	}
	//nahoøe
	if (pozadi.jeTamStrom(this->zombi.getPos().x + 10, this->zombi.getPos().y)) {
		stromy[2] = false;
	}
	else if (pozadi.jeTamStrom(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y)) {
		stromy[2] = false;
	}
	//dole
	if (pozadi.jeTamStrom(this->zombi.getPos().x + 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		stromy[3] = false;
	}
	else if (pozadi.jeTamStrom(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		stromy[3] = false;
	}

	//skály
	bool skaly[] = {true, true, true, true};
	//levá strana
	if (pozadi.jeTamSkala(this->zombi.getPos().x, this->zombi.getPos().y + 10) && this->smer == "Leva") {
		skaly[0] = false;
	}
	else if (pozadi.jeTamSkala(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10) && this->smer == "Leva") {
		skaly[0] = false;
	}
	//pravá strana
	if (pozadi.jeTamSkala(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + 10) && this->smer == "Prava") {
		skaly[1] = false;
	}
	else if (pozadi.jeTamSkala(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10) && this->smer == "Prava") {
		skaly[1] = false;
	}
	//nahoøe
	if (pozadi.jeTamSkala(this->zombi.getPos().x + 10, this->zombi.getPos().y)) {
		skaly[2] = false;
	}
	else if (pozadi.jeTamSkala(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y)) {
		skaly[2] = false;
	}
	//dole
	if (pozadi.jeTamSkala(this->zombi.getPos().x + 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		skaly[3] = false;
	}
	else if (pozadi.jeTamSkala(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		skaly[3] = false;
	}


	//kameny
	bool kamene[] = {true, true, true, true};
	//levá strana
	if (kameny.kontrolaPrekryti(this->zombi.getPos().x, this->zombi.getPos().y + 10)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[0] = false;
	}
	else if (kameny.kontrolaPrekryti(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y / 2)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[0] = false;
	}
	else if (kameny.kontrolaPrekryti(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[0] = false;
	}
	//pravá strana
	if (kameny.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + 10)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[1] = false;
	}
	else if (kameny.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y / 2)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[1] = false;
	}
	else if (kameny.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[1] = false;
	}
	//horní strana
	if (kameny.kontrolaPrekryti(this->zombi.getPos().x + 10, this->zombi.getPos().y)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[2] = false;
	}
	else if (kameny.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[2] = false;
	}
	//dolní strana
	if (kameny.kontrolaPrekryti(this->zombi.getPos().x + 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[3] = false;
	}
	else if (kameny.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		this->index_prvku = kameny.index;
		this->hit_kamen = true;
		kamene[3] = false;
	}
	
	if (kamene[0] && kamene[1] && kamene[2] && kamene[3]) {
		this->hit_kamen = false;
	}

	//døeva
	bool drevak[] = {true, true, true, true};
	//levá strana
	if (dreva.kontrolaPrekryti(this->zombi.getPos().x, this->zombi.getPos().y + 10)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[0] = false;
	}
	else if (dreva.kontrolaPrekryti(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y / 2)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[0] = false;
	}
	else if (dreva.kontrolaPrekryti(this->zombi.getPos().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[0] = false;
	}
	//pravá strana
	if (dreva.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + 10)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[1] = false;
	}
	else if (dreva.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y / 2)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[1] = false;
	}
	else if (dreva.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x, this->zombi.getPos().y + this->zombi.getGlobalBounds().y - 10)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[1] = false;
	}
	//horní strana
	if (dreva.kontrolaPrekryti(this->zombi.getPos().x + 10, this->zombi.getPos().y)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[2] = false;
	}
	else if (dreva.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[2] = false;
	}
	//dolní strana
	if (dreva.kontrolaPrekryti(this->zombi.getPos().x + 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[3] = false;
	}
	else if (dreva.kontrolaPrekryti(this->zombi.getPos().x + this->zombi.getGlobalBounds().x - 10, this->zombi.getPos().y + this->zombi.getGlobalBounds().y)) {
		this->index_prvku = dreva.index;
		this->hit_drevo = true;
		drevak[3] = false;
	}

	if (drevak[0] && drevak[1] && drevak[2] && drevak[3]) {
		this->hit_drevo = false;
	}


	if (stromy[0] && skaly[0] && kamene[0] && drevak[0])
		this->leva = true;
	else
		this->leva = false;

	if (stromy[1] && skaly[1] && kamene[1] && drevak[1])
		this->prava = true;
	else
		this->prava = false;

	if (stromy[2] && skaly[2] && kamene[2] && drevak[2])
		this->nahore = true;
	else
		this->nahore = false;

	if (stromy[3] && skaly[3] && kamene[3] && drevak[3])
		this->dole = true;
	else
		this->dole = false;
}

//Funkce která pohybuje se zombíkem podle toho kde se nachází hráè a kde má zombí volnou cestu
void Zombi::pohyb(Hrac* hrac) {
	int posun = 50;
	if (hrac->getPos().x + hrac->getGlobalBounds().x / 2 < this->zombi.getPos().x && hrac->getPos().y + hrac->getGlobalBounds().y < this->zombi.getPos().y) {
		if (this->leva && this->nahore) {
			this->smer = "Leva";
			this->zombi.nastaveniObrazku("Zombici/Zombi_do_leva1.png");
			this->pozice = 1;

			sf::Vector2f cil;
			cil.x = hrac->getPos().x + hrac->getGlobalBounds().x / 2;
			cil.y = hrac->getPos().y + hrac->getGlobalBounds().y - 5;

			sf::Vector2f start;
			start.x = this->zombi.getPos().x;
			start.y = this->zombi.getPos().y;

			this->pohybProHrace((cil.x - start.x) / posun, (cil.y - start.y) / posun);
		}
		else if (!this->leva && this->nahore && this->strana == "") {
			this->pohybProHrace(0, -this->posun);
		}
		else if (this->leva && !this->nahore && this->strana == "") {
			this->pohybProHrace(-this->posun, 0);
		}
		else if ((!this->leva && !this->nahore) || this->strana == "dole" || this->strana == "prava") {
			if (this->dole && this->strana != "prava") {
				this->strana = "dole";
				this->pohybProHrace(0, this->posun);
			}
			else {
				this->strana = "prava";
				this->pohybProHrace(this->posun, 0);
			}
		}

		if (this->strana == "dole" && this->leva) {
			this->strana = "";
		}
		else if (this->strana == "prava" && this->nahore) {
			this->strana = "";
		}
	}
	else if (hrac->getPos().x + hrac->getGlobalBounds().x / 2 > this->zombi.getPos().x + this->zombi.getGlobalBounds().x && hrac->getPos().y + hrac->getGlobalBounds().y < this->zombi.getPos().y) {
		if (this->prava && this->nahore) {
			this->smer = "Prava";
			this->zombi.nastaveniObrazku("Zombici/Zombi_do_prava1.png");
			this->pozice = 1;

			sf::Vector2f cil;
			cil.x = hrac->getPos().x + hrac->getGlobalBounds().x / 2;
			cil.y = hrac->getPos().y + hrac->getGlobalBounds().y - 5;

			sf::Vector2f start;
			start.x = this->zombi.getPos().x + this->zombi.getGlobalBounds().x;
			start.y = this->zombi.getPos().y;

			this->pohybProHrace((cil.x - start.x) / posun, (cil.y - start.y) / posun);
		}
		else if (!this->prava && this->nahore && this->strana == "") {
			this->pohybProHrace(0, -this->posun);
		}
		else if (this->prava && !this->nahore && this->strana == "") {
			this->pohybProHrace(this->posun, 0);
		}
		else if ((!this->prava && !this->nahore) || this->strana == "dole" || this->strana == "leva") {
			if (this->dole && this->strana != "leva") {
				this->strana = "dole";
				this->pohybProHrace(0, this->posun);
			}
			else {
				this->strana = "leva";
				this->pohybProHrace(-this->posun, 0);
			}
		}

		if (this->strana == "dole" && this->prava) {
			this->strana = "";
		}
		else if (this->strana == "leva" && this->nahore) {
			this->strana = "";
		}
	}
	else if (hrac->getPos().x + hrac->getGlobalBounds().x / 2 > this->zombi.getPos().x + this->zombi.getGlobalBounds().x && hrac->getPos().y > this->zombi.getPos().y + this->zombi.getGlobalBounds().y) {
		if (this->prava && this->dole) {
			this->smer = "Prava";
			this->zombi.nastaveniObrazku("Zombici/Zombi_do_prava1.png");
			this->pozice = 1;

			sf::Vector2f cil;
			cil.x = hrac->getPos().x + hrac->getGlobalBounds().x / 2;
			cil.y = hrac->getPos().y + 5;

			sf::Vector2f start;
			start.x = this->zombi.getPos().x + this->zombi.getGlobalBounds().x;
			start.y = this->zombi.getPos().y + this->zombi.getGlobalBounds().y;

			this->pohybProHrace((cil.x - start.x) / posun, (cil.y - start.y) / posun);
		}
		else if (!this->prava && this->dole && this->strana == "") {
			this->pohybProHrace(0, this->posun);
		}
		else if (this->prava && !this->dole && this->strana == "") {
			this->pohybProHrace(this->posun, 0);
		}
		else if ((!this->prava && !this->dole) || this->strana == "nahore" || this->strana == "leva") {
			if (this->nahore && this->strana != "leva") {
				this->strana = "nahore";
				this->pohybProHrace(0, -this->posun);
			}
			else {
				this->strana = "leva";
				this->pohybProHrace(-this->posun, 0);
			}
		}

		if (this->strana == "nahore" && this->prava) {
			this->strana = "";
		}
		else if (this->strana == "leva" && this->dole) {
			this->strana = "";
		}
	}
	else if (hrac->getPos().x + hrac->getGlobalBounds().x / 2 < this->zombi.getPos().x && hrac->getPos().y > this->zombi.getPos().y + this->zombi.getGlobalBounds().y) {
		if (this->leva && this->dole) {
			this->smer = "Leva";
			this->zombi.nastaveniObrazku("Zombici/Zombi_do_leva1.png");
			this->pozice = 1;

			sf::Vector2f cil;
			cil.x = hrac->getPos().x + hrac->getGlobalBounds().x / 2;
			cil.y = hrac->getPos().y + 5;

			sf::Vector2f start;
			start.x = this->zombi.getPos().x;
			start.y = this->zombi.getPos().y + this->zombi.getGlobalBounds().y;

			this->pohybProHrace((cil.x - start.x) / posun, (cil.y - start.y) / posun);
		}
		else if (!this->leva && this->dole && this->strana == "") {
			this->pohybProHrace(0, this->posun);
		}
		else if (this->leva && !this->dole && this->strana == "") {
			this->pohybProHrace(-this->posun, 0);
		}
		else if ((!this->leva && !this->dole) || this->strana == "nahore" || this->strana == "prava") {
			if (this->nahore && this->strana != "prava") {
				this->strana = "nahore";
				this->pohybProHrace(0, -this->posun);
			}
			else {
				this->strana = "prava";
				this->pohybProHrace(this->posun, 0);
			}
		}

		if (this->strana == "nahore" && this->leva) {
			this->strana = "";
		}
		else if (this->strana == "prava" && this->dole) {
			this->strana = "";
		}
	}
	else {
		if (hrac->getPos().x + hrac->getGlobalBounds().x < this->zombi.getPos().x) {
			if (this->leva) {
				this->smer = "Leva";
				this->zombi.nastaveniObrazku("Zombici/Zombi_do_leva1.png");
				this->pozice = 1;

				this->pohybProHrace(-this->posun, 0);
			}
			else if (this->nahore || this->strana == "nahore") {
				this->strana = "nahore";
				this->pohybProHrace(0, -this->posun);
			}
			else if (this->dole || this->strana == "dole") {
				this->strana = "dole";
				this->pohybProHrace(0, this->posun);
			}
		}
		else if (hrac->getPos().x > this->zombi.getPos().x + this->zombi.getGlobalBounds().x) {
			if (this->prava) {
				this->smer = "Prava";
				this->zombi.nastaveniObrazku("Zombici/Zombi_do_prava1.png");
				this->pozice = 1;

				this->pohybProHrace(this->posun, 0);
			}
			else if (this->nahore || this->strana == "nahore") {
				this->strana = "nahore";
				this->pohybProHrace(0, -this->posun);
			}
			else if (this->dole || this->strana == "dole") {
				this->strana = "dole";
				this->pohybProHrace(0, this->posun);
			}
		}

		if (hrac->getPos().y + hrac->getGlobalBounds().y < this->zombi.getPos().y) {
			if (this->nahore) {
				this->pohybProHrace(0, -this->posun);
			}
			else if (this->leva || this->strana == "leva") {
				this->strana = "leva";
				this->pohybProHrace(-this->posun, 0);
			}
			else if (this->prava || this->strana == "prava") {
				this->strana = "prava";
				this->pohybProHrace(this->posun, 0);
			}
		}
		else if (hrac->getPos().y > this->zombi.getPos().y + this->zombi.getGlobalBounds().y) {
			if (this->dole) {
				this->pohybProHrace(0, this->posun);
			}
			else if (this->leva || this->strana == "leva") {
				this->strana = "leva";
				this->pohybProHrace(-this->posun, 0);
			}
			else if (this->prava || this->strana == "prava") {
				this->strana = "prava";
				this->pohybProHrace(this->posun, 0);
			}
		}
	}
	
	if (this->leva && this->prava && this->dole && this->nahore) {
		this->strana = "";
	}
}