#pragma once
#include "Textura.h"
#include "Text.h"

class Tlacitko
{
public:
	sf::RectangleShape tvar;
	Text text;

	sf::Color hlavni_barva;
	sf::Color barva_po_prejeti;
	sf::Color barva_po_kliknuti;

	sf::Color hlavni_barva_textu;
	sf::Color barva_po_prejeti_textu;
	sf::Color barva_po_kliknuti_textu;

	void render(sf::RenderTarget* ono);
	void nastaveni(std::string nazev, float x, float y, 
		sf::Color hlavni_barva, sf::Color barva_po_prejeti, sf::Color barva_po_kliknuti, 
		sf::Color hlavni_barva_textu, sf::Color barva_po_prejeti_textu, sf::Color barva_po_kliknuti_textu);
	void update(sf::Vector2f pozice_kurzoru);
};