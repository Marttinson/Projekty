#include "Hra.h"

Hra::Hra() {
	this->initVariables();
	this->initWindow();
	//this->initEnemies();
	this->initFonts();
	this->initText();
}

Hra::~Hra() {
	delete this->window;
}

//privatni funkce

void Hra::initFonts() {
	if (!this->font.loadFromFile("Fonts/Roboto-Black.ttf")) {
		cout << "ERROR::INITFONT::Failde to load font!" << endl;
	}
}

void Hra::initText() {
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(18);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE");
}

void Hra::initVariables() {
	this->window = nullptr;

	//hrení logika
	this->endGame = false;
	this->health = 20;
	this->points = 0;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 8;
	this->mouseHeld = true;
}

void Hra::initWindow() {
	//video.getDesktopMode();	//dostane hodnoty z obrazovky
	this->video.height = 600;
	this->video.width = 800;

	this->window = new RenderWindow(VideoMode(video.width, video.height), "Moje první hra", Style::Titlebar | Style::Close | Style::Resize);

	this->window->setFramerateLimit(60);
}

/*void Hra::initEnemies() {
	this->enemy.setPosition(Vector2f(10.f, 10.f));	//pozice
	this->enemy.setSize(Vector2f(100.f, 100.f));	//veliost
	//this->enemy.setScale(Vector2f(0.5f, 0.5f));		//vynásobí hodnotou velikost - mùže zmenšovat nebo zvìtšovat
	this->enemy.setFillColor(Color::Cyan);			//barva
	//this->enemy.setOutlineColor(Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}*/

//funkce

void Hra::renderText(RenderTarget& target) {
	target.draw(this->uiText);
}

void Hra::updateText() {
	stringstream ss;
	ss << "Points: " << this->points << endl << "Health: " << this->health << endl;

	this->uiText.setString(ss.str());
}

void Hra::spawnEnemy() {
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 
		0.f
	);

	//randomized enemy type
	int type = rand() % 5;

	switch (type) {
	case 0:
		this->enemy.setSize(Vector2f(10.f, 10.f));
		this->enemy.setFillColor(Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(Vector2f(30.f, 30.f));
		this->enemy.setFillColor(Color::Blue);
		break;
	case 2:
		this->enemy.setSize(Vector2f(50.f, 50.f));
		this->enemy.setFillColor(Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(Vector2f(70.f, 70.f));
		this->enemy.setFillColor(Color::Red);
		break;
	case 4:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::Green);
		break;
	default:
		break;
	}

	//spawn enemy
	this->enemies.push_back(this->enemy);

	//remove enemies at end of screen

}

void Hra::updateEnemies() {
	//updating timer for enemy spawning
	if ((int)this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer++;
	}

	
	//moving and updating enemies
	for (int i = 0; i < (int)this->enemies.size(); i++) {

		this->enemies[i].move(0.f, 5.f);

		//if the enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->health--;
			cout << "hp: " << this->health << endl;
		}

	}

	//check if clicked upon
	if (Mouse::isButtonPressed(Mouse::Left)) {
		
		if (this->mouseHeld) {
			
			bool deleted = false;

			for (int i = 0; i < (int)this->enemies.size() && !deleted; i++) {
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					
					//gain points
					if (this->enemies[i].getFillColor() == Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == Color::Red)
						this->points += 30;
					else if (this->enemies[i].getFillColor() == Color::Green)
						this->points += 1;

					cout << "pointy: " << this->points << endl;


					deleted = true;
					if (this->mouseHeld)
						this->enemies.erase(this->enemies.begin() + i);
					this->mouseHeld = false;
				}
			}
		}
	}
	else
		this->mouseHeld = true;
}

void Hra::renderEnemies(RenderTarget& target) {
	//render all the enemies
	for (auto& e : this->enemies) {
		target.draw(e);
	}
}

void Hra::updateMousePosition() {
	this->mousePosWindow = Mouse::getPosition(*this->window);

	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Hra::eventLoop() {
	//Event loop
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type)
		{
			//když se zavøe
		case Event::Closed:
			this->window->close();
			break;

			//když se zmaèkne nìjaký tlaèítko
		case Event::KeyPressed:

			//ESC
			if (ev.key.code == Keyboard::Escape)
				this->window->close();
			break;

		default:
			break;
		}
	}
}

void Hra::update() {
	this->eventLoop();

	if (!endGame) {
		this->updateMousePosition();

		//update mouse position

		//relativní v celé obrazovce - 0, 0 je v levém horním rohu obrazovky
		//cout << "Mouse pos: " << Mouse::getPosition().x << " " << Mouse::getPosition().y << endl;

		//relativní v oknì - 0, 0 je v levém horním rohu okna
		//cout << "Mouse pos: " << Mouse::getPosition(*this->window).x << " " << Mouse::getPosition(*this->window).y << endl;

		this->updateText();

		this->updateEnemies();
	}

	//endgame condition
	if (this->health <= 0)
		this->endGame = true;
}

void Hra::render() {
	this->window->clear();

	//kresleni
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}

//gettery
bool Hra::running() const{
	return this->window->isOpen();
}

bool Hra::getEndGame() const {
	return this->endGame;
}
