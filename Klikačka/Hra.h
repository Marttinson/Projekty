#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

//trida ktera nahrazuje game engine

class Hra
{
private:
	//promeny
	//window
	RenderWindow* window;
	VideoMode video;
	Event ev;

	//mouse position
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Resources
	Font font;

	//text
	Text uiText;

	//herní logika
	bool endGame;
	unsigned int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//herní objekty
	vector<RectangleShape> enemies;
	RectangleShape enemy;

	//privatni funkce
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();
public:
	//konstruktor a dekonstruktor
	Hra();
	~Hra();

	//funkce
	void spawnEnemy();
	void updateMousePosition();
	void eventLoop();
	void updateEnemies();
	void update();
	void updateText();
	void renderEnemies(RenderTarget& target);
	void render();
	void renderText(RenderTarget& target);

	//gettery
	bool running() const;
	bool getEndGame() const;
};

