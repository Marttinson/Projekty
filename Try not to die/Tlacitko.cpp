#include "Tlacitko.h"

//Vykreslení tlaèítka
void Tlacitko::render(sf::RenderTarget* okno) {
	okno->draw(this->tvar);
	this->text.render(okno);
}

//Nastavení hodnot tlaèítka podle parametrù funkce
void Tlacitko::nastaveni(std::string nazev, float x, float y, 
	sf::Color hlavni_barva, sf::Color barva_po_prejeti, sf::Color barva_po_kliknuti,
	sf::Color hlavni_barva_textu, sf::Color barva_po_prejeti_textu, sf::Color barva_po_kliknuti_textu) 
{
	this->hlavni_barva = hlavni_barva;
	this->barva_po_prejeti = barva_po_prejeti;
	this->barva_po_kliknuti = barva_po_kliknuti;
	
	this->hlavni_barva_textu = hlavni_barva_textu;
	this->barva_po_prejeti_textu = barva_po_prejeti_textu;
	this->barva_po_kliknuti_textu = barva_po_kliknuti_textu;
	
	this->tvar.setSize(sf::Vector2f(x, y));
	this->tvar.setFillColor(hlavni_barva);

	this->text.text.setFillColor(this->hlavni_barva_textu);
	this->text.setString(nazev);
}

//Funkce která aktualizuje stav tlaèítka, mìní mu barvu po pøejetí kurzorem nebo po kliknutí
void Tlacitko::update(sf::Vector2f pozice_kurzoru) {
	if (this->tvar.getGlobalBounds().contains(pozice_kurzoru)) {
		this->tvar.setFillColor(this->barva_po_prejeti);
		this->text.text.setFillColor(this->barva_po_prejeti_textu);
	}
	else if (!this->tvar.getGlobalBounds().contains(pozice_kurzoru)) {
		this->tvar.setFillColor(this->hlavni_barva);
		this->text.text.setFillColor(this->hlavni_barva_textu);
	}

	if (this->tvar.getGlobalBounds().contains(pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->tvar.setFillColor(this->barva_po_kliknuti);
		this->text.text.setFillColor(this->barva_po_kliknuti_textu);
	}
	else if (!this->tvar.getGlobalBounds().contains(pozice_kurzoru) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->tvar.setFillColor(this->hlavni_barva);
		this->text.text.setFillColor(this->hlavni_barva_textu);
	}
}