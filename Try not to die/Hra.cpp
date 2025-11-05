#include "Hra.h"
//Inicializace promìnných
Hra::Hra() {
	this->nastaveniOkna();

	this->vMenu = true;
	this->menu.nastaveni(this->rozliseni);
	this->jednou = true;
	this->konec = false;
}

//Uvolnìní pamìti
Hra::~Hra() {
	delete this->okno;
	delete this->hrac;

	for (int i = 0; i < this->pozadi.velikost_hraci_plochy; i++) {
		delete[] this->pozadi.prvek[i];
	}
	delete[] this->pozadi.prvek;
	delete[] this->pozadi.skaly.prvek;
	delete[] this->pozadi.stromy.prvek;
	delete[] this->dreva.drevo;
	delete[] this->kameny.kamen;
	delete[] this->zombici.zombici;
}

void Hra::nastaveniOkna() {
	this->okno = new sf::RenderWindow(sf::VideoMode(), "Try not to die", sf::Style::Fullscreen);

	this->okno->setFramerateLimit(60);

	this->rozliseni.x = this->okno->getSize().x;
	this->rozliseni.y = this->okno->getSize().y;
}

void Hra::hraj() {
	//Herní cyklus
	while (this->running()) {
		this->update();
		
		this->render();
	}
}

//Inicializace promìnných po stisknutí tlaèítka hrát v menu
void Hra::startHry() {
	this->hrac = new Hrac(this->rozliseni);
	this->hrac->setPos((this->rozliseni.x / 2) - (this->hrac->getGlobalBounds().x / 2), (this->rozliseni.y / 2) - (this->hrac->getGlobalBounds().y / 2));
	this->hrac->naplneniInv(this->rozliseni);
	this->poradi_vybraneho = 1;

	this->pozadi.naplnPozadi(this->rozliseni, this->hrac);

	this->hrac->pistol[0].nastaveniObrazku("Hrac/Pistol.png");
	this->hrac->pistol[0].setPos(this->hrac->getPos().x + this->hrac->getGlobalBounds().x - 75, this->hrac->getPos().y + this->hrac->getGlobalBounds().y - 95);

	this->hrac->pistol[1].nastaveniObrazku("Hrac/Strelba.png");
	this->hrac->pistol[1].setPos(this->hrac->getPos().x + this->hrac->getGlobalBounds().x - 75, this->hrac->getPos().y + this->hrac->getGlobalBounds().y - 95);

	this->hrac->sekera.setPos(this->hrac->getPos().x + this->hrac->getGlobalBounds().x - 65, this->hrac->getPos().y + this->hrac->getGlobalBounds().y - 55);
	this->hrac->krumpac.setPos(this->hrac->getPos().x + this->hrac->getGlobalBounds().x - 65, this->hrac->getPos().y + this->hrac->getGlobalBounds().y - 55);
	this->hrac->vybranejItem(1);

	this->esc.nastaveni(this->rozliseni);

	this->veHre = true;
	this->ESC = false;
}

//Funkce která vykresluje pøedmìty na obrazovku
void Hra::render() {
	this->okno->clear();

	if (!this->vMenu) {
		this->pozadi.renderPozadi(this->okno);
		this->dreva.render(this->okno);
		this->kameny.render(this->okno);
		this->hrac->render(this->okno);
		this->renderGear();
		this->strelba.render(this->okno);
		this->zombici.render(this->okno);
		
		if (this->ESC) {
			this->esc.render(this->okno);
		}
	}
	else if (this->vMenu) {
		this->menu.render(this->okno);
	}

	if (this->konec) {
		this->hrob.render(this->okno);
		this->koncici_tlacitko.render(this->okno);
		this->koncici_text.render(this->okno);
	}

	this->okno->display();
}

//Funkce která vykresluje aktuálnì používaný nástroj hráèe
void Hra::renderGear() {
	if (this->ovladani.vybrano == "Pistol")
		this->hrac->pistol[0].render(this->okno);
	else if (this->ovladani.vybrano == "Strelba")
		this->hrac->pistol[1].render(this->okno);
	else if (this->ovladani.vybrano == "Sekera")
		this->hrac->sekera.render(this->okno);
	else if (this->ovladani.vybrano == "Krumpac")
		this->hrac->krumpac.render(this->okno);
}

//Funkce která postupnì volá další funkce a tím aktualizuje hodnoty, pohyb a celkový dìj
void Hra::update() {
	this->eventLoop();
	this->updateKurzor();
	this->updateTlacitkaESC();

	if (this->veHre) {
		if (this->ESC && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->ESC = false;
		if (!this->ESC && !this->konec) {
			this->ovladani.updateTlacitek(this->pozadi, this->hrac, this->dreva, this->kameny, this->cas_na_pohyb, this->ev, this->uhel, this->pozice_kurzoru, this->strelba, this->zombici);
			this->zombici.update(this->pozadi, this->kameny, this->dreva, this->hrac);
			this->strelba.update(this->cas_na_pohyb, this->dreva, this->kameny, this->pozadi, this->zombici, this->hrac);
			this->updateTextu();
			if (this->hrac->hp <= 0)
				this->konecHry();

			this->hrac->inv[2].setPocet(this->dreva.pocet_dreva);
			this->hrac->inv[4].setPocet(this->kameny.pocet_kamene);
		}
	}
	else if (this->vMenu) {
		this->menu.update(this->pozice_kurzoru);
		this->updateMenu();
	}
	else if (this->ESC) {
		this->esc.update(this->pozice_kurzoru);
		this->updateESC();
	}
	if (this->konec) {
		this->koncici_tlacitko.update(this->pozice_kurzoru);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->koncici_tlacitko.tvar.getGlobalBounds().contains(this->pozice_kurzoru)) {
			this->okno->close();
		}
	}
}

void Hra::eventLoop() {
	while (this->okno->pollEvent(this->ev)) {

		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->okno->close();
			break;

		default:
			break;
		}
	}
}

//Funkce která aktualizuje pozici kurzoru a natoèení nástrojù
void Hra::updateKurzor() {
	this->pozice_kurzoru = this->okno->mapPixelToCoords(sf::Mouse::getPosition(*this->okno));

	if (this->veHre && !this->ESC && !this->konec) {
		double a, b;
		sf::Vector2i kurzor = sf::Mouse::getPosition(*this->okno);

		if (this->ovladani.vybrano == "Pistol") {
			a = (double)kurzor.x - this->hrac->pistol[0].getPos().x;
			b = (double)kurzor.y - this->hrac->pistol[0].getPos().y;

			this->uhel = (-atan2(a, b) * 180 / M_PI) + 90;
			this->hrac->pistol[0].setRotate(this->uhel);
		}
		else if (this->ovladani.vybrano == "Strelba") {
			a = (double)kurzor.x - this->hrac->pistol[1].getPos().x;
			b = (double)kurzor.y - this->hrac->pistol[1].getPos().y;

			this->uhel = (-atan2(a, b) * 180 / M_PI) + 90;
			this->hrac->pistol[1].setRotate(this->uhel);
		}
		else if (this->ovladani.vybrano == "Sekera") {
			a = (double)kurzor.x - this->hrac->sekera.getPos().x;
			b = (double)kurzor.y - this->hrac->sekera.getPos().y;

			this->uhel = (-atan2(a, b) * 180 / M_PI) + 35;
			this->hrac->sekera.setRotate(this->uhel);
		}
		else if (this->ovladani.vybrano == "Krumpac") {
			a = (double)kurzor.x - this->hrac->krumpac.getPos().x;
			b = (double)kurzor.y - this->hrac->krumpac.getPos().y;

			this->uhel = (-atan2(a, b) * 180 / M_PI) + 45;
			this->hrac->krumpac.setRotate(this->uhel);
		}
	}
}

//Funkce která aktualizuje dìní, když se uživatel nachází v menu
void Hra::updateMenu() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->menu.nova_hra.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && this->jednou && this->vMenu) {
		this->jednou = false;
		this->startHry();
		this->vMenu = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->menu.konec.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && this->jednou && this->vMenu) {
		this->jednou = false;
		this->okno->close();
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->jednou = true;
}

//Funkce která hodnotí co se stane po stisku tlaèítka ESC
void Hra::updateTlacitkaESC() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->jednou) {
		this->jednou = false;
		if (this->vMenu) {
			this->okno->close();
		}
		else if (this->veHre) {
			this->ESC = true;
			this->veHre = false;
		}
		else if (this->ESC) {
			this->ESC = false;
			this->veHre = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->jednou = true;
	}
}

//Funkce která aktualizuje dìní, když se uživatel nachází v ESC
void Hra::updateESC() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->esc.pokracovat.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && this->jednou && this->ESC) {
		this->jednou = false;
		this->veHre = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->esc.konec.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && this->jednou && this->ESC) {
		this->jednou = false;
		this->okno->close();
	}
}

//Funkce která aktualizuje text, podle hodnot které má zobrazovat
void Hra::updateTextu() {
	this->hrac->txt_hp.setString("HP: " + std::to_string(this->hrac->hp) + " / 100");
	this->hrac->txt_hp.text.setPosition(this->rozliseni.x - this->hrac->txt_hp.text.getGlobalBounds().width - 20, 20);

	this->zombici.text.setString("Zabito zombi: " + std::to_string(this->zombici.zabitych_zombiku));
	this->zombici.text.text.setPosition(this->rozliseni.x - this->zombici.text.text.getGlobalBounds().width - 20, this->hrac->txt_hp.text.getPosition().y + this->hrac->txt_hp.text.getGlobalBounds().height + 20);
}

//Funkce kterí vypíše konec hry, celkové skóre, ...
void Hra::konecHry() {
	this->konec = true;
	this->veHre = false;

	this->koncici_tlacitko.nastaveni("Ukoncit", 400, 75, sf::Color::Black, sf::Color(20, 20, 20), sf::Color(210, 210, 210), sf::Color(240, 240, 240), sf::Color::White, sf::Color(60, 60, 60));
	this->koncici_tlacitko.tvar.setPosition(this->rozliseni.x / 2 - this->koncici_tlacitko.tvar.getGlobalBounds().width / 2, this->rozliseni.y / 2 - this->koncici_tlacitko.tvar.getLocalBounds().height / 2);
	this->koncici_tlacitko.text.nastaveniTextu("HelpMe", 40, "Ukoncit");
	this->koncici_tlacitko.text.setPosition(this->koncici_tlacitko.tvar);

	this->koncici_text.nastaveniTextu("HelpMe", 40, sf::Color::Magenta, "Zabil jsi: " + std::to_string(this->zombici.zabitych_zombiku));
	this->koncici_text.text.setPosition(this->rozliseni.x / 2 - this->koncici_text.text.getGlobalBounds().width / 2, this->koncici_tlacitko.tvar.getPosition().y - 100);

	this->hrob.nastaveniObrazku("Textury/Hrob.png");
	this->hrob.setPos(this->rozliseni.x / 2 - this->hrob.getGlobalBounds().x / 2, this->rozliseni.y / 2 - this->hrob.getGlobalBounds().y / 2 - 150);
}

//Funkce která vrací hodnotu zda program bìží èi nikoliv
bool Hra::running(){
	return this->okno->isOpen();
}