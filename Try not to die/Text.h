#pragma once
#include "Textura.h"

class Text
{
public:
	sf::Font font;
	sf::Text text;

	void render(sf::RenderTarget* okno);
	void nastaveniFontu(std::string font);
	void nastaveniTextu(std::string font, int velikost, std::string text);
	void nastaveniTextu(std::string font, int velikost, sf::Color barva);
	void nastaveniTextu(std::string font, int velikost, sf::Color barva, std::string text);

	void setString(std::string text);
	void setPosition(sf::RectangleShape tvar);
};