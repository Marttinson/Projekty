#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Policko
{
private:

	sf::Font font;
	sf::Text text;

	void nastaveniText();
	void nastaveniFont();

public:
	bool zmacknuto;
	bool pravy_zmacknuto;
	bool pindaJednou;
	std::string barva;
	sf::RectangleShape tvar;
	sf::Image obrazek;
	sf::Texture textura;
	sf::Sprite vypln;
	std::string figurka;

	Policko();
	~Policko();

	//funkce
	void render(sf::RenderTarget* target);

	//settery
	void setSouradnice(float x, float y);
	void setText(std::string text);
	void setBarvaTextu(sf::Color barva);
	void setVelikost(float x, float y);
	void setBarvuPozadi(sf::Color barva);
	void nastaveniObrazku(std::string cesta, std::string figurka);
	void nastaveniObrazku(std::string cesta, std::string figurka, std::string barva);
	void nastaveniObrazku(Policko policko);

	//gettery
	std::string getText();
	sf::Color getBarvaTextu();
};

