#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Tlacitko
{
private:
	
	sf::Font font;
	sf::Text text;

	void nastaveniText();
	void nastaveniFont();

public:
	bool zmacknuto;
	bool pravy_zmacknuto;
	sf::RectangleShape tvar;
	Tlacitko();
	~Tlacitko();

	//funkce
	void update(sf::Vector2f pozice_kurzoru);
	void render(sf::RenderTarget* target);

	//settery
	void setSouradnice(float x, float y);
	void setText(std::string text);
	void setBarvaTextu(sf::Color barva);
	void setVelikost(float x, float y);
	void setBarvuPozadi(sf::Color barva);

	//gettery
	std::string getText();
	sf::Color getBarvaTextu();
};

