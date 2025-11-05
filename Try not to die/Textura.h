#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Textura
{
protected:
	sf::Image obrazek;
	sf::Texture textura;

public:
	Textura();

	sf::Sprite vypln;
	std::string obsah;
	int hp;

	virtual void nastaveniObrazku(std::string cesta);
	void nastaveniTravy();
	void nastaveniVody();
	void nastaveniSkaly();
	void nastaveniZbytkuPoSkale();
	void nastaveniStromu();
	void nastaveniParezu();
	void nastaveniDreva();
	void nastaveniKamene();
	void nastaveniStrelby();
	void nastaveniStrely();

	virtual void render(sf::RenderTarget* okno);

	virtual void pohyb(float x, float y);

	//settery
	void setPos(float x, float y);
	void setRotate(double uhel);

	//gettery
	sf::Vector2f getGlobalBounds();
	sf::Vector2f getPos();
};