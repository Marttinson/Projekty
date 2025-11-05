#include "Hrac.h"

//Inicializace promìnných
Hrac::Hrac(sf::Vector2f velikost) {
	this->nastaveniObrazku("Hrac/Bezi_do_prava.png");

	this->krumpac.nastaveniObrazku("Hrac/Krumpac.png");
	this->sekera.nastaveniObrazku("Hrac/Sekera.png");

	this->hp = 100;
	this->txt_hp.nastaveniTextu("Dosis-Light", 32, sf::Color::Magenta);

	this->naplneniInv(velikost);

	this->vybrana_pozice.setSize(sf::Vector2f(56, 56));
	this->vybrana_pozice.setFillColor(sf::Color(180, 180, 180));

	this->na_skale = false;
}

//Uvolnìní pamìti
Hrac::~Hrac() {
	delete[] this->inv;
}

//Naplnìní inventáøe
void Hrac::naplneniInv(sf::Vector2f velikost) {
	this->inv = new Inventar[5];

	int y = velikost.y - 60;
	this->inv[0].zalozeniInv(1, "Hrac/Pistol_inv.png", velikost.x / 2 - 135, y);
	this->inv[1].zalozeniInv(2, "Hrac/Sekera_inv.png", velikost.x / 2 - 80, y);
	this->inv[2].zalozeniInv(3, "Hrac/Drevo_textura_inv.png", velikost.x / 2 - 25, y, true);
	this->inv[3].zalozeniInv(4, "Hrac/Krumpac_inv.png", velikost.x / 2 + 30, y);
	this->inv[4].zalozeniInv(5, "Hrac/Kamen_textura_inv.png", velikost.x / 2 + 85, y, true);
}

//Funkce která vykreslí za používané náøadí ètverec, aby šlo lépe poznat
void Hrac::vybranejItem(int poradi) {
	this->vybrana_pozice.setPosition(this->inv[poradi - 1].getPos().x - 3, this->inv[poradi - 1].getPos().y - 3);
}

//Funkce která vykreslí hráèe, inventáø a další potøebné vìci
void Hrac::render(sf::RenderTarget* okno) {
	okno->draw(this->vypln);
	okno->draw(this->vybrana_pozice);
	for (int i = 0; i < 5; i++)
		this->inv[i].render(okno);
	this->txt_hp.render(okno);
}