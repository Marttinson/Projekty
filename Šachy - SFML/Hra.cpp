#include "Hra.h"

//cervena 255, 25, 50
//zelena 47, 178, 71
//pozadi 120, 120, 120
//tmavsi seda 60, 60, 60
//svetlejsi seda 210, 210, 210

//Konstrukotr a dekonstruktor
Hra::Hra() {
	this->zmacknuto = false;
	this->jednou = true;
	this->pocet_kol = 1;

	//hraci plocha
	this->naplneniHraciPlochy();
	this->vyplnFigurek();
	this->nic.loadFromFile("Figurky/nic.png");

	//okno
	this->nastaveniOkna();
	this->nastaveniText();
}

Hra::~Hra() {
	delete this->okno;

	for (int i = 0; i < 8; i++) {
		delete[] this->hraci_plocha[i];
	}
	delete[] this->hraci_plocha;
}

//--------------------------------------------------------------------------------------------------------------------

//funkce pro konstruktor
void Hra::nastaveniOkna() {
	this->video.height = 895;	//845
	this->video.width = 895;

	this->okno = new sf::RenderWindow(sf::VideoMode(this->video.width, this->video.height), "Sachy", sf::Style::Close | sf::Style::Titlebar);
	
	this->okno->setFramerateLimit(60);
}

void Hra::nastaveniFont() {
	if (!this->font.loadFromFile("Fonts/Roboto-Black.ttf")) {
		std::cout << "ERROR::INITFONT::Failde to load font!" << std::endl;
	}
}

void Hra::nastaveniText() {
	this->nastaveniFont();
	for (int i = 0; i < 16; i++) {
		this->text[i].setFont(this->font);
		this->text[i].setCharacterSize(18);
		this->text[i].setFillColor(sf::Color::White);
		this->text[i].setString("");
	}

	for (int i = 0; i < 8; i++) {
		this->text[i].setString(std::to_string(i + 1));
		this->text[i].setPosition(9, this->hraci_plocha[i][0].tvar.getPosition().y + this->hraci_plocha[i][0].tvar.getGlobalBounds().height / 2 - 9);
	}
	for (int i = 0; i < 8; i++) {
		char znak = 'A' + i;
		this->text[i + 8].setString(znak);
		this->text[i + 8].setPosition(this->hraci_plocha[0][i].tvar.getPosition().x + this->hraci_plocha[0][i].tvar.getGlobalBounds().width / 2 - 9, 5);
	}
}

//--------------------------------------------------------------------------------------------------------------------

//privatni funkce


//--------------------------------------------------------------------------------------------------------------------

//funkce
void Hra::hraj() {
	while (this->running()) {
		this->update();

		this->render();
	}
}

void Hra::render() {
	this->vykresleniHraciPlochy();
	this->renderText();
	this->okno->display();
}

void Hra::renderText() {
	for (int i = 0; i < 16; i++) {
		this->okno->draw(this->text[i]);
	}
}

void Hra::update() {
	this->kurzorUpdate();
	this->eventLoop();

	this->prirazeniBarvy();
	this->updatePindu();
	this->updateHraciPlochy();
}

void Hra::prirazeniBarvy() {
	if (this->pocet_kol % 2 == 1) {
		this->barva = "bila";
	}
	else {
		this->barva = "cerna";
	}
}

void Hra::updatePindu() {
	for (int i = 0; i < 8; i++) {
		if (this->hraci_plocha[0][i].figurka == "pinda") {
			this->hraci_plocha[0][i].nastaveniObrazku("Figurky/Bila_kralovna.png", "kralovna");
		}
		if (this->hraci_plocha[7][i].figurka == "pinda") {
			this->hraci_plocha[7][i].nastaveniObrazku("Figurky/Cerna_kralovna.png", "kralovna");
		}
	}
}

void Hra::updateHraciPlochy() {
	this->okno->clear(sf::Color(120, 120, 120));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hraci_plocha[i][j].tvar.getGlobalBounds().contains(this->pozice_kurzoru) && !this->hraci_plocha[i][j].zmacknuto && !zmacknuto) {
				this->hraci_plocha[i][j].zmacknuto = true;
				this->zmacknuto = true;
				bool klik = true;

				if (this->hraci_plocha[i][j].tvar.getFillColor() == sf::Color(47, 178, 71) || this->hraci_plocha[i][j].tvar.getFillColor() == sf::Color(255, 25, 50)) {
					if (this->hraci_plocha[this->y][this->x].figurka == "pinda") {
						this->hraci_plocha[this->y][this->x].pindaJednou = false;
					}
					hraci_plocha[i][j].vypln.setTexture(*this->hraci_plocha[this->y][this->x].vypln.getTexture());
					this->hraci_plocha[i][j].nastaveniObrazku(this->hraci_plocha[this->y][this->x]);
					this->hraci_plocha[this->y][this->x].vypln.setTexture(nic);
					this->hraci_plocha[this->y][this->x].figurka = "";
					klik = false;
					this->pocet_kol++;
					//std::cout << pocet_kol << std::endl;
				}

				if (!this->jednou) {
					this->jednou = true;
					this->zbarveniHraciPlochy();
				}

				if (this->hraci_plocha[i][j].barva == this->barva) {
					if (this->hraci_plocha[i][j].figurka == "pinda" && klik) {
						this->pohybPinda(j, i);
						this->jednou = false;
					}
					else if (this->hraci_plocha[i][j].figurka == "vez" && klik) {
						this->pohybVez(j, i);
						this->jednou = false;
					}
					else if (this->hraci_plocha[i][j].figurka == "kun" && klik) {
						this->pohybKun(j, i);
						this->jednou = false;
					}
					else if (this->hraci_plocha[i][j].figurka == "strelec" && klik) {
						this->pohybStrelec(j, i);
						this->jednou = false;
					}
					else if (this->hraci_plocha[i][j].figurka == "kralovna" && klik) {
						this->pohybKralovna(j, i);
						this->jednou = false;
					}
					else if (this->hraci_plocha[i][j].figurka == "kral" && klik) {
						this->pohybKral(j, i);
						this->jednou = false;
					}
				}
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->hraci_plocha[i][j].zmacknuto = false;
				this->zmacknuto = false;
			}
		}
	}
}

void Hra::zbarveniHraciPlochy() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(210, 210, 210));
				}
				else {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(60, 60, 60));
				}
			}
			else {
				if (j % 2 == 0) {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(60, 60, 60));
				}
				else {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(210, 210, 210));
				}
			}
		}
	}
}

void Hra::naplneniHraciPlochy() {
	float x = 30;
	float y = 30;
	this->hraci_plocha = new Policko*[8];
	for (int i = 0; i < 8; i++) {
		this->hraci_plocha[i] = new Policko[8];
		for (int j = 0; j < 8; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(210, 210, 210));
				}
				else {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(60, 60, 60));
				}
			}
			else {
				if (j % 2 == 0) {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(60, 60, 60));
				}
				else {
					this->hraci_plocha[i][j].setBarvuPozadi(sf::Color(210, 210, 210));
				}
			}
			this->hraci_plocha[i][j].setVelikost(100, 100);
			this->hraci_plocha[i][j].setSouradnice(x, y);
			x += 105;
		}
		x = 30;
		y += 105;
	}
}

void Hra::vykresleniHraciPlochy() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->hraci_plocha[i][j].render(this->okno);
		}
	}
}

void Hra::vyplnFigurek() {
	this->hraci_plocha[0][0].nastaveniObrazku("Figurky/Cerna_vez.png", "vez", "cerna");
	this->hraci_plocha[0][1].nastaveniObrazku("Figurky/Cerna_kun.png", "kun", "cerna");
	this->hraci_plocha[0][2].nastaveniObrazku("Figurky/Cerna_jezdec.png", "strelec", "cerna");
	this->hraci_plocha[0][3].nastaveniObrazku("Figurky/Cerna_kralovna.png", "kralovna", "cerna");
	this->hraci_plocha[0][4].nastaveniObrazku("Figurky/Cerna_kral.png", "kral", "cerna");
	this->hraci_plocha[0][5].nastaveniObrazku("Figurky/Cerna_jezdec.png", "strelec", "cerna");
	this->hraci_plocha[0][6].nastaveniObrazku("Figurky/Cerna_kun.png", "kun", "cerna");
	this->hraci_plocha[0][7].nastaveniObrazku("Figurky/Cerna_vez.png", "vez", "cerna");

	for (int i = 0; i < 8; i++) {
		this->hraci_plocha[1][i].nastaveniObrazku("Figurky/Cerna_pinda.png", "pinda", "cerna");
	}

	this->hraci_plocha[7][0].nastaveniObrazku("Figurky/Bila_vez.png", "vez", "bila");
	this->hraci_plocha[7][1].nastaveniObrazku("Figurky/Bila_kun.png", "kun", "bila");
	this->hraci_plocha[7][2].nastaveniObrazku("Figurky/Bila_jezdec.png", "strelec", "bila");
	this->hraci_plocha[7][3].nastaveniObrazku("Figurky/Bila_kralovna.png", "kralovna", "bila");
	this->hraci_plocha[7][4].nastaveniObrazku("Figurky/Bila_kral.png", "kral", "bila");
	this->hraci_plocha[7][5].nastaveniObrazku("Figurky/Bila_jezdec.png", "strelec", "bila");
	this->hraci_plocha[7][6].nastaveniObrazku("Figurky/Bila_kun.png", "kun", "bila");
	this->hraci_plocha[7][7].nastaveniObrazku("Figurky/Bila_vez.png", "vez", "bila");

	for (int i = 0; i < 8; i++) {
		this->hraci_plocha[6][i].nastaveniObrazku("Figurky/Bila_pinda.png", "pinda", "bila");
	}
}

void Hra::kurzorUpdate() {
	this->pozice_kurzoru = this->okno->mapPixelToCoords(sf::Mouse::getPosition(*this->okno));
	//std::cout << this->pozice_kurzoru.x << " y: " << this->pozice_kurzoru.y << std::endl;
}

void Hra::eventLoop() {
	//Event loop
	while (this->okno->pollEvent(this->ev)) {

		switch (this->ev.type)
		{
			//když se zavøe
		case sf::Event::Closed:
			this->okno->close();
			break;

			//když se zmaèkne nìjaký tlaèítko
		case sf::Event::KeyPressed:

			//ESC
			if (ev.key.code == sf::Keyboard::Escape)
				this->okno->close();
			break;

		default:
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------
//pohyby
void Hra::pohybPinda(int x, int y) {
	if (this->hraci_plocha[y][x].barva == "cerna") {
		if (y < 7) {
			if (x == 0) {
				if (this->hraci_plocha[y + 1][1].figurka != "" && this->hraci_plocha[y + 1][1].barva != "cerna") {
					this->hraci_plocha[y + 1][1].tvar.setFillColor(sf::Color(255, 25, 50));
				}
			}
			else if (x == 7) {
				if (this->hraci_plocha[y + 1][6].figurka != "" && this->hraci_plocha[y + 1][6].barva != "cerna") {
					this->hraci_plocha[y + 1][6].tvar.setFillColor(sf::Color(255, 25, 50));
				}
			}
			else {
				if (this->hraci_plocha[y + 1][x - 1].figurka != "" && this->hraci_plocha[y + 1][x - 1].barva != "cerna") {
					this->hraci_plocha[y + 1][x - 1].tvar.setFillColor(sf::Color(255, 25, 50));
				}
				if (this->hraci_plocha[y + 1][x + 1].figurka != "" && this->hraci_plocha[y + 1][x + 1].barva != "cerna") {
					this->hraci_plocha[y + 1][x + 1].tvar.setFillColor(sf::Color(255, 25, 50));
				}
			}

			//-----
			if (this->hraci_plocha[y][x].pindaJednou && this->hraci_plocha[y + 1][x].figurka == "") {
				this->hraci_plocha[y + 1][x].tvar.setFillColor(sf::Color(47, 178, 71));
				this->hraci_plocha[y + 2][x].tvar.setFillColor(sf::Color(47, 178, 71));
			}
			else if (this->hraci_plocha[y + 1][x].figurka == "") {
				this->hraci_plocha[y + 1][x].tvar.setFillColor(sf::Color(47, 178, 71));
			}
		}
	}
	else {
		if (y > 0) {
			if (x == 0) {
				if (this->hraci_plocha[y - 1][1].figurka != "" && this->hraci_plocha[y - 1][1].barva != "bila") {
					this->hraci_plocha[y - 1][1].tvar.setFillColor(sf::Color(255, 25, 50));
				}
			}
			else if (x == 7) {
				if (this->hraci_plocha[y - 1][6].figurka != "" && this->hraci_plocha[y - 1][6].barva != "bila") {
					this->hraci_plocha[y - 1][6].tvar.setFillColor(sf::Color(255, 25, 50));
				}
			}
			else {
				if (this->hraci_plocha[y - 1][x - 1].figurka != "" && this->hraci_plocha[y - 1][x - 1].barva != "bila") {
					this->hraci_plocha[y - 1][x - 1].tvar.setFillColor(sf::Color(255, 25, 50));
				}
				if (this->hraci_plocha[y - 1][x + 1].figurka != "" && this->hraci_plocha[y - 1][x + 1].barva != "bila") {
					this->hraci_plocha[y - 1][x + 1].tvar.setFillColor(sf::Color(255, 25, 50));
				}
			}
			//-----
			if (this->hraci_plocha[y][x].pindaJednou && this->hraci_plocha[y - 1][x].figurka == "") {
				this->hraci_plocha[y - 1][x].tvar.setFillColor(sf::Color(47, 178, 71));
				this->hraci_plocha[y - 2][x].tvar.setFillColor(sf::Color(47, 178, 71));

			}
			else if (this->hraci_plocha[y - 1][x].figurka == "") {
				if (y > 0)
					this->hraci_plocha[y - 1][x].tvar.setFillColor(sf::Color(47, 178, 71));
			}
		}
	}
	this->x = x;
	this->y = y;
}

void Hra::pohybVez(int x, int y) {
	if (y < 7) {
		int posun = y;
		do {
			posun++;
			this->pohyb(x, posun, x, y);
		} while (this->hraci_plocha[posun][x].figurka == "" && posun != 7);
	}
	if (y > 0) {
		int posun = y;
		do {
			posun--;
			this->pohyb(x, posun, x, y);
		} while (this->hraci_plocha[posun][x].figurka == "" && posun != 0);
	}
	if (x < 7) {
		int posun = x;
		do {
			posun++;
			this->pohyb(posun, y, x, y);
		} while (this->hraci_plocha[y][posun].figurka == "" && posun != 7);
	}
	if (x > 0) {
		int posun = x;
		do {
			posun--;
			this->pohyb(posun, y, x, y);
		} while (this->hraci_plocha[y][posun].figurka == "" && posun != 0);
	}
	
	this->x = x;
	this->y = y;
}

void Hra::pohybKun(int x, int y) {
	int posunX = x - 1;
	int posunY = y - 2;
	if (posunX >= 0 && posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x + 1;
	posunY = y - 2;
	if (posunX < 8 && posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x - 2;
	posunY = y - 1;
	if (posunX >= 0 && posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x + 2;
	posunY = y - 1;
	if (posunX < 8 && posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x - 1;
	posunY = y + 2;
	if (posunX >= 0 && posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x + 1;
	posunY = y + 2;
	if (posunX < 8 && posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x - 2;
	posunY = y + 1;
	if (posunX >= 0 && posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}

	posunX = x + 2;
	posunY = y + 1;
	if (posunX < 8 && posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}
	this->x = x;
	this->y = y;
}

void Hra::pohybStrelec(int x, int y) {
	if (x < 7 && y > 0) {
		int posunX = x;
		int posunY = y;
		do {
			posunX++;
			posunY--;
			this->pohyb(posunX, posunY, x, y);
		} while (this->hraci_plocha[posunY][posunX].figurka == "" && posunX != 7 && posunY != 0);
	}
	if (x < 7 && y < 7) {
		int posunX = x;
		int posunY = y;
		do {
			posunX++;
			posunY++;
			this->pohyb(posunX, posunY, x, y);
		} while (this->hraci_plocha[posunY][posunX].figurka == "" && posunX != 7 && posunY != 7);
	}
	if (x > 0 && y > 0) {
		int posunX = x;
		int posunY = y;
		do {
			posunX--;
			posunY--;
			this->pohyb(posunX, posunY, x, y);
		} while (this->hraci_plocha[posunY][posunX].figurka == "" && posunX != 0 && posunY != 0);
	}
	if (x > 0 && y < 7) {
		int posunX = x;
		int posunY = y;
		do {
			posunX--;
			posunY++;
			this->pohyb(posunX, posunY, x, y);
		} while (this->hraci_plocha[posunY][posunX].figurka == "" && posunX != 0 && posunY != 7);
	}
	this->x = x;
	this->y = y;
}

void Hra::pohybKralovna(int x, int y) {
	this->pohybStrelec(x, y);
	this->pohybVez(x, y);
}

void Hra::pohybKral(int x, int y) {
	int posunX = x - 1;
	int posunY = y - 1;
	if (posunX >= 0 && posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x;
	posunY = y - 1;
	if (posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x + 1;
	posunY = y - 1;
	if (posunX < 8 && posunY >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x - 1;
	posunY = y;
	if (posunX >= 0) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x + 1;
	posunY = y;
	if (posunX < 8) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x - 1;
	posunY = y + 1;
	if (posunX >= 0 && posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x;
	posunY = y + 1;
	if (posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}
	posunX = x + 1;
	posunY = y + 1;
	if (posunX < 8 && posunY < 8) {
		this->pohyb(posunX, posunY, x, y);
	}
	this->x = x;
	this->y = y;
}

void Hra::pohyb(int posunX, int posunY, int x, int y) {
	if (this->hraci_plocha[posunY][posunX].figurka == "")
		this->hraci_plocha[posunY][posunX].tvar.setFillColor(sf::Color(47, 178, 71));
	else if (this->hraci_plocha[posunY][posunX].barva != this->hraci_plocha[y][x].barva) {
		this->hraci_plocha[posunY][posunX].tvar.setFillColor(sf::Color(255, 25, 50));
	}
	
}

//gettery
bool Hra::running(){
	return this->okno->isOpen();
}