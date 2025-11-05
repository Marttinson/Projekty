#include "Ovladani.h"

//Inicializace promìnných
Ovladani::Ovladani() {
	this->zmacknuto = false;
	this->pohyb = "Prava";
	this->vybrano = "Pistol";
	this->kaceni_stromu.nastaveni("Kaceni_stromu", 50);
	this->tezeni_kamene.nastaveni("Tezeni_kamene", 50);
	this->pokladani_dreva.nastaveni("Pokladani_dreva", 50);
	this->pokladani_kamene.nastaveni("Pokladani_kamene", 50);
}

//Funkce která kontroluje vstupy uživatele a podle nich volá další funkce
void Ovladani::updateTlacitek(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, sf::Event ev, double uhel, sf::Vector2f pozice_kurzoru, Strelba& strelba, Zombici& zombici) {
	bool neni = true;
	for (int i = 0; i < pozadi.skaly.pocet_prvku; i++) {
		if (pozadi.jeTamSkala(hrac->getPos().x, hrac->getPos().y)) {
			neni = false;
		}
		else if (pozadi.jeTamSkala(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y)) {
			neni = false;
		}
		else if (pozadi.jeTamSkala(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y)) {
			neni = false;
		}
		else if (pozadi.jeTamSkala(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y)) {
			neni = false;
		}
	}
	if (neni)
		hrac->na_skale = false;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->tlacitkoW(pozadi, hrac, dreva, kameny, cas_na_pohyb, zombici, strelba);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->tlacitkoS(pozadi, hrac, dreva, kameny, cas_na_pohyb, zombici, strelba);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->tlacitkoA(pozadi, hrac, dreva, kameny, cas_na_pohyb, zombici, strelba);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->pohyb == "Leva") {
		hrac->nastaveniObrazku("Hrac/Cuci_do_leva.png");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->tlacitkoD(pozadi, hrac, dreva, kameny, cas_na_pohyb, zombici, strelba);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->pohyb == "Prava") {
		hrac->nastaveniObrazku("Hrac/Cuci_do_prava.png");
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->tlacitkoMezernik(pozadi, hrac);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->levyTlacitko(pozadi, hrac, dreva, kameny, uhel, pozice_kurzoru, strelba);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !this->zmacknuto) {
		this->zmacknuto = true;
		this->tlacitko1(hrac, uhel);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !this->zmacknuto) {
		this->zmacknuto = true;
		this->tlacitko2(hrac, uhel);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !this->zmacknuto) {
		this->zmacknuto = true;
		this->tlacitko3(hrac, uhel);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !this->zmacknuto) {
		this->zmacknuto = true;
		this->tlacitko4(hrac, uhel);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !this->zmacknuto) {
		this->zmacknuto = true;
		this->tlacitko5(hrac, uhel);
	}
	else if (ev.type == sf::Event::MouseWheelScrolled && !this->zmacknuto) {
		this->poradi_vybraneho -= ev.mouseWheelScroll.delta;
		if (this->poradi_vybraneho > 5)
			this->poradi_vybraneho = 1;
		else if (this->poradi_vybraneho < 1)
			this->poradi_vybraneho = 5;

		if (this->poradi_vybraneho == 1)
			this->tlacitko1(hrac, uhel);
		else if (this->poradi_vybraneho == 2)
			this->tlacitko2(hrac, uhel);
		else if (this->poradi_vybraneho == 3)
			this->tlacitko3(hrac, uhel);
		else if (this->poradi_vybraneho == 4)
			this->tlacitko4(hrac, uhel);
		else if (this->poradi_vybraneho == 5)
			this->tlacitko5(hrac, uhel);

		this->zmacknuto = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) &&
		ev.type != sf::Event::MouseWheelScrolled
		) {
		this->zmacknuto = false;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->vybrano == "Strelba") {
		this->vybrano = "Pistol";
		hrac->pistol[0].setRotate(uhel);
		strelba.pauza = 20;
	}
}

//Funkce která kontroluje zda se hráè mùže pohybovat smìrem nahoru a když ano tak udìlá vše co je k tomu potøeba
void Ovladani::tlacitkoW(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba) {
	bool zavazi = false;
	for (int i = 0; i < pozadi.stromy.pocet_prvku; i++) {
		if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
		else if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
	}

	if (!zavazi) {
		for (int i = 0; i < pozadi.skaly.pocet_prvku; i++) {
			if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
			else if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < dreva.pocet_prvku; i++) {
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x / 2, hrac->getPos().y)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y)) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < kameny.pocet_prvku; i++) {
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x / 2, hrac->getPos().y) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
		}
	}

	if (pozadi.prvek[5][5].getPos().y < hrac->getPos().y && !zavazi) {
		pozadi.pohyb(0, 10);
		pozadi.stromy.pohyb(0, 10);
		pozadi.skaly.pohyb(0, 10);
		dreva.pohyb(0, 10);
		kameny.pohyb(0, 10);
		zombici.pohypProHrace(0, 10);
		strelba.pohypProHrace(0, 10);
		if (this->pohyb == "Leva") {
			if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 0) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_leva1.png");
			}
			else if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 1) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_leva.png");
			}
		}
		else {
			if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 0) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_prava1.png");
			}
			else if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 1) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_prava.png");
			}
		}
	}
	else if (this->pohyb == "Leva")
		hrac->nastaveniObrazku("Hrac/Cuci_do_leva.png");
	else
		hrac->nastaveniObrazku("Hrac/Cuci_do_prava.png");
}

//Funkce která kontroluje zda se hráè mùže pohybovat smìrem dolù a když ano tak udìlá vše co je k tomu potøeba
void Ovladani::tlacitkoS(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba) {
	bool zavazi = false;
	for (int i = 0; i < pozadi.stromy.pocet_prvku; i++) {
		if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y + hrac->getGlobalBounds().y) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
		else if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y + hrac->getGlobalBounds().y) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
	}

	if (!zavazi) {
		for (int i = 0; i < pozadi.skaly.pocet_prvku; i++) {
			if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y + hrac->getGlobalBounds().y) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
			else if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y + hrac->getGlobalBounds().y) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < dreva.pocet_prvku; i++) {
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y + hrac->getGlobalBounds().y)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x / 2, hrac->getPos().y + hrac->getGlobalBounds().y)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y + hrac->getGlobalBounds().y)) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < kameny.pocet_prvku; i++) {
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + 20, hrac->getPos().y + hrac->getGlobalBounds().y) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x / 2, hrac->getPos().y + hrac->getGlobalBounds().y) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x - 20, hrac->getPos().y + hrac->getGlobalBounds().y) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
		}
	}

	if (pozadi.prvek[30][30].getPos().y > hrac->getPos().y + hrac->getGlobalBounds().y && !zavazi) {
		pozadi.pohyb(0, -10);
		pozadi.stromy.pohyb(0, -10);
		pozadi.skaly.pohyb(0, -10);
		dreva.pohyb(0, -10);
		kameny.pohyb(0, -10);
		zombici.pohypProHrace(0, -10);
		strelba.pohypProHrace(0, -10);
		if (this->pohyb == "Leva") {
			if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 0) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_leva1.png");
			}
			else if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 1) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_leva.png");
			}
		}
		else {
			if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 0) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_prava1.png");
			}
			else if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 1) {
				hrac->nastaveniObrazku("Hrac/Bezi_do_prava.png");
			}
		}
	}
	else if (this->pohyb == "Leva")
		hrac->nastaveniObrazku("Hrac/Cuci_do_leva.png");
	else
		hrac->nastaveniObrazku("Hrac/Cuci_do_prava.png");
}

//Funkce která kontroluje zda se hráè mùže pohybovat smìrem do leva a když ano tak udìlá vše co je k tomu potøeba
void Ovladani::tlacitkoA(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba) {
	bool zavazi = false;
	for (int i = 0; i < pozadi.stromy.pocet_prvku; i++) {
		if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + 20) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
		else if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
	}

	if (!zavazi) {
		for (int i = 0; i < pozadi.skaly.pocet_prvku; i++) {
			if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + 20) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
			else if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < dreva.pocet_prvku; i++) {
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + 20)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y / 2)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20)) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < kameny.pocet_prvku; i++) {
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + 20) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y / 2) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
		}
	}

	if (pozadi.prvek[5][5].getPos().x < hrac->getPos().x && !zavazi) {
		if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 0) {
			hrac->nastaveniObrazku("Hrac/Bezi_do_leva1.png");
		}
		else if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 1) {
			hrac->nastaveniObrazku("Hrac/Bezi_do_leva.png");
		}
		pozadi.pohyb(10, 0);
		pozadi.stromy.pohyb(10, 0);
		pozadi.skaly.pohyb(10, 0);
		dreva.pohyb(10, 0);
		kameny.pohyb(10, 0);
		zombici.pohypProHrace(10, 0);
		strelba.pohypProHrace(10, 0);

		this->pohyb = "Leva";
	}
	else if (this->pohyb == "Leva" && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		hrac->nastaveniObrazku("Hrac/Cuci_do_leva.png");
	else if (this->pohyb == "Prava" && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		hrac->nastaveniObrazku("Hrac/Cuci_do_prava.png");
}

//Funkce která kontroluje zda se hráè mùže pohybovat smìrem do prava a když ano tak udìlá vše co je k tomu potøeba
void Ovladani::tlacitkoD(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, sf::Clock cas_na_pohyb, Zombici& zombici, Strelba& strelba) {
	bool zavazi = false;
	for (int i = 0; i < pozadi.stromy.pocet_prvku; i++) {
		if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + 20) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
		else if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20) && pozadi.stromy.prvek[i].obsah == "Strom") {
			zavazi = true;
			break;
		}
	}

	if (!zavazi) {
		for (int i = 0; i < pozadi.skaly.pocet_prvku; i++) {
			if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + 20) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
			else if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20) && pozadi.skaly.prvek[i].obsah == "Skala" && !hrac->na_skale) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < dreva.pocet_prvku; i++) {
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + 20)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y / 2)) {
				zavazi = true;
				break;
			}
			else if (dreva.drevo[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20)) {
				zavazi = true;
				break;
			}
		}
	}

	if (!zavazi) {
		for (int i = 0; i < kameny.pocet_prvku; i++) {
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + 20) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y / 2) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
			else if (kameny.kamen[i].vypln.getGlobalBounds().contains(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y - 20) && kameny.kamen[i].hp > 0) {
				zavazi = true;
				break;
			}
		}
	}

	if (pozadi.prvek[30][30].getPos().x - hrac->getGlobalBounds().x - 5 > hrac->getPos().x && !zavazi) {
		if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 0) {
			hrac->nastaveniObrazku("Hrac/Bezi_do_prava1.png");
		}
		else if ((int)floor(cas_na_pohyb.getElapsedTime().asMilliseconds()) % 2 == 1) {
			hrac->nastaveniObrazku("Hrac/Bezi_do_prava.png");
		}
		pozadi.pohyb(-10, 0);
		pozadi.stromy.pohyb(-10, 0);
		pozadi.skaly.pohyb(-10, 0);
		dreva.pohyb(-10, 0);
		kameny.pohyb(-10, 0);
		zombici.pohypProHrace(-10, 0);
		strelba.pohypProHrace(-10, 0);

		this->pohyb = "Prava";
	}
	else if (this->pohyb == "Leva" && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		hrac->nastaveniObrazku("Hrac/Cuci_do_leva.png");
	else if (this->pohyb == "Prava" && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		hrac->nastaveniObrazku("Hrac/Cuci_do_prava.png");
}

//Funkce která se zavolá po stiku mezerníku a umožní hráèi pøejít pøes kámen
void Ovladani::tlacitkoMezernik(Pozadi& pozadi, Hrac* hrac) {
	if (pozadi.jeTamSkala(hrac->getPos().x, hrac->getPos().y)) {
		hrac->na_skale = true;
	}
	else if (pozadi.jeTamSkala(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y)) {
		hrac->na_skale = true;
	}
	else if (pozadi.jeTamSkala(hrac->getPos().x, hrac->getPos().y + hrac->getGlobalBounds().y)) {
		hrac->na_skale = true;
	}
	else if (pozadi.jeTamSkala(hrac->getPos().x + hrac->getGlobalBounds().x, hrac->getPos().y + hrac->getGlobalBounds().y)) {
		hrac->na_skale = true;
	}
}

//Funkce která se zavolá po stisku 1 a pøiøadí hráèi nástroj na této pozici
void Ovladani::tlacitko1(Hrac* hrac, double uhel) {
	this->vybrano = "Pistol";
	this->poradi_vybraneho = 1;
	hrac->vybranejItem(1);
	hrac->pistol[0].setRotate(uhel);
}

//Funkce která se zavolá po stisku 2 a pøiøadí hráèi nástroj na této pozici
void Ovladani::tlacitko2(Hrac* hrac, double uhel) {
	this->vybrano = "Sekera";
	this->poradi_vybraneho = 2;
	hrac->vybranejItem(2);
	hrac->sekera.setRotate(uhel);
}

//Funkce která se zavolá po stisku 3 a pøiøadí hráèi nástroj na této pozici
void Ovladani::tlacitko3(Hrac* hrac, double uhel) {
	this->vybrano = "Drevo";
	this->poradi_vybraneho = 3;
	hrac->vybranejItem(3);
}

//Funkce která se zavolá po stisku 4 a pøiøadí hráèi nástroj na této pozici
void Ovladani::tlacitko4(Hrac* hrac, double uhel) {
	this->vybrano = "Krumpac";
	this->poradi_vybraneho = 4;
	hrac->vybranejItem(4);
	hrac->krumpac.setRotate(uhel);
}

//Funkce která se zavolá po stisku 5 a pøiøadí hráèi nástroj na této pozici
void Ovladani::tlacitko5(Hrac* hrac, double uhel) {
	this->vybrano = "Kamen";
	this->poradi_vybraneho = 5;
	hrac->vybranejItem(5);
}

//Funkce která vrátí true pokud je na souøadnicích volno pro umístìní bloku nebo false pokud tomu tak není
bool Ovladani::kontrolaUmisteni(std::string material, Pozadi pozadi, Dreva dreva, Kameny kameny, Hrac* hrac, sf::Vector2f pozice_kurzoru) {
	if (material == "Drevo") {
		for (int i = 0; i < kameny.pocet_prvku; i++) {
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x - 50, pozice_kurzoru.y - 50)) {
				return true;
			}
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x + 50, pozice_kurzoru.y - 50)) {
				return true;
			}
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x - 50, pozice_kurzoru.y + 50)) {
				return true;
			}
			if (kameny.kamen[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x + 50, pozice_kurzoru.y + 50)) {
				return true;
			}
		}
	}
	else if (material == "Kamen") {
		for (int i = 0; i < dreva.pocet_prvku; i++) {
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x - 50, pozice_kurzoru.y - 50)) {
				return true;
			}
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x + 50, pozice_kurzoru.y - 50)) {
				return true;
			}
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x - 50, pozice_kurzoru.y + 50)) {
				return true;
			}
			if (dreva.drevo[i].vypln.getGlobalBounds().contains(pozice_kurzoru.x + 50, pozice_kurzoru.y + 50)) {
				return true;
			}
		}
	}

	if (pozadi.pozadiNaSouradnici(pozice_kurzoru.x - 50, pozice_kurzoru.y - 50) == "Voda")
		return true;
	else if (pozadi.pozadiNaSouradnici(pozice_kurzoru.x + 50, pozice_kurzoru.y - 50) == "Voda")
		return true;
	else if (pozadi.pozadiNaSouradnici(pozice_kurzoru.x - 50, pozice_kurzoru.y + 50) == "Voda")
		return true;
	else if (pozadi.pozadiNaSouradnici(pozice_kurzoru.x + 50, pozice_kurzoru.y + 50) == "Voda")
		return true;

	if (hrac->vypln.getGlobalBounds().contains(pozice_kurzoru.x - 50, pozice_kurzoru.y - 50))
		return true;
	else if (hrac->vypln.getGlobalBounds().contains(pozice_kurzoru.x + 50, pozice_kurzoru.y - 50))
		return true;
	else if (hrac->vypln.getGlobalBounds().contains(pozice_kurzoru.x - 50, pozice_kurzoru.y + 50))
		return true;
	else if (hrac->vypln.getGlobalBounds().contains(pozice_kurzoru.x + 50, pozice_kurzoru.y + 50))
		return true;

	if (pozadi.jeTamStrom(pozice_kurzoru.x - 50, pozice_kurzoru.y - 50))
		return true;
	else if (pozadi.jeTamStrom(pozice_kurzoru.x + 50, pozice_kurzoru.y - 50))
		return true;
	else if (pozadi.jeTamStrom(pozice_kurzoru.x - 50, pozice_kurzoru.y + 50))
		return true;
	else if (pozadi.jeTamStrom(pozice_kurzoru.x + 50, pozice_kurzoru.y + 50))
		return true;

	if (pozadi.jeTamSkala(pozice_kurzoru.x - 50, pozice_kurzoru.y - 50))
		return true;
	else if (pozadi.jeTamSkala(pozice_kurzoru.x + 50, pozice_kurzoru.y - 50))
		return true;
	else if (pozadi.jeTamSkala(pozice_kurzoru.x - 50, pozice_kurzoru.y + 50))
		return true;
	else if (pozadi.jeTamSkala(pozice_kurzoru.x + 50, pozice_kurzoru.y + 50))
		return true;

	return false;
}

//Funkce která se zavolá po stisknutí levého tlaèítka na myši
void Ovladani::levyTlacitko(Pozadi& pozadi, Hrac* hrac, Dreva& dreva, Kameny& kameny, double uhel, sf::Vector2f pozice_kurzoru, Strelba& strelba) {
	if (this->vybrano == "Pistol" || this->vybrano == "Strelba") {
		this->vybrano = "Strelba";
		hrac->pistol[1].setRotate(uhel);

		double alfa, beta, gama;
		double a, b, c;
		
		if (hrac->pistol[1].vypln.getRotation() > 0 && hrac->pistol[1].vypln.getRotation() < 90) {
			gama = 90;
			alfa = hrac->pistol[1].vypln.getRotation();
			beta = gama - alfa;

			c = 110;
			a = c * cos(alfa * M_PI / 180);
			b = c * cos(beta * M_PI / 180);

			strelba.pridat(sf::Vector2f(hrac->pistol[1].getPos().x + a, hrac->pistol[1].getPos().y + b), uhel, pozice_kurzoru);
		}
		else if (hrac->pistol[1].vypln.getRotation() > 90 && hrac->pistol[1].vypln.getRotation() < 180) {
			gama = 90;
			alfa = hrac->pistol[1].vypln.getRotation() - 90;
			beta = gama - alfa;

			c = 110;
			a = c * sin(alfa * M_PI / 180);
			b = c * sin(beta * M_PI / 180);

			strelba.pridat(sf::Vector2f(hrac->pistol[1].getPos().x - a, hrac->pistol[1].getPos().y + b), uhel, pozice_kurzoru);
		}
		else if (hrac->pistol[1].vypln.getRotation() > 180 && hrac->pistol[1].vypln.getRotation() < 270) {
			gama = 90;
			alfa = hrac->pistol[1].vypln.getRotation() - 180;
			beta = gama - alfa;

			c = 110;
			a = c * cos(alfa * M_PI / 180);
			b = c * cos(beta * M_PI / 180);

			strelba.pridat(sf::Vector2f(hrac->pistol[1].getPos().x - a, hrac->pistol[1].getPos().y - b), uhel, pozice_kurzoru);
		}
		else if (hrac->pistol[1].vypln.getRotation() > 270 && hrac->pistol[1].vypln.getRotation() < 360) {
			gama = 90;
			alfa = hrac->pistol[1].vypln.getRotation() - 270;
			beta = gama - alfa;

			c = 110;
			a = c * sin(alfa * M_PI / 180);
			b = c * sin(beta * M_PI / 180);

			strelba.pridat(sf::Vector2f(hrac->pistol[1].getPos().x + a, hrac->pistol[1].getPos().y - b), uhel, pozice_kurzoru);
		}
	}
	else if (this->vybrano == "Sekera") {
		for (int i = 0; i < pozadi.stromy.pocet_prvku; i++) {
			if (pozadi.stromy.prvek[i].vypln.getGlobalBounds().contains(pozice_kurzoru) && pozadi.stromy.prvek[i].obsah == "Strom" && !this->zmacknuto) {
				pozadi.stromy.prvek[i].hp--;
				this->kaceni_stromu.zvuk.play();
				if (pozadi.stromy.prvek[i].hp == 0) {
					float x = pozadi.stromy.prvek[i].getPos().x + 52;
					float y = pozadi.stromy.prvek[i].getPos().y + 150;
					pozadi.stromy.prvek[i].nastaveniParezu();
					pozadi.stromy.prvek[i].setPos(x, y);
					dreva.pocet_dreva++;
				}
			}
		}
		this->zmacknuto = true;
	}
	else if (this->vybrano == "Drevo") {
		if (dreva.pocet_dreva != 0 && !kontrolaUmisteni("Drevo", pozadi, dreva, kameny, hrac, pozice_kurzoru)) {
			if (dreva.zkontrolovat(pozice_kurzoru)) {
				this->pokladani_dreva.zvuk.play();
				dreva.pridatPrvek(pozice_kurzoru);
				dreva.pocet_dreva--;
			}
		}
	}
	else if (this->vybrano == "Krumpac") {
		for (int i = 0; i < pozadi.skaly.pocet_prvku; i++) {
			if (pozadi.skaly.prvek[i].vypln.getGlobalBounds().contains(pozice_kurzoru) && pozadi.skaly.prvek[i].obsah == "Skala" && !this->zmacknuto) {
				pozadi.skaly.prvek[i].hp--;
				this->tezeni_kamene.zvuk.play();
				if (pozadi.skaly.prvek[i].hp == 0) {
					float x = pozadi.skaly.prvek[i].getPos().x + pozadi.skaly.prvek[i].getGlobalBounds().x / 2 - 32;
					float y = pozadi.skaly.prvek[i].getPos().y + pozadi.skaly.prvek[i].getGlobalBounds().y - 70;
					pozadi.skaly.prvek[i].nastaveniZbytkuPoSkale();
					pozadi.skaly.prvek[i].setPos(x, y);
					kameny.pocet_kamene++;
				}
			}
		}
		this->zmacknuto = true;
	}
	else if (this->vybrano == "Kamen") {
		if (kameny.pocet_kamene != 0 && !kontrolaUmisteni("Kamen", pozadi, dreva, kameny, hrac, pozice_kurzoru)) {
			if (kameny.zkontrolovat(pozice_kurzoru)) {
				this->pokladani_kamene.zvuk.play();
				kameny.pridatPrvek(pozice_kurzoru);
				kameny.pocet_kamene--;
			}
		}
	}
}