#include "Hra.h"


//Konstrukotr a dekonstruktor
Hra::Hra() {
	this->jednou = true;
	this->tah = 0;
	this->na_vyhru = 3;
	this->velikost = 10;
	this->vyhrano = false;
	this->hra_zacala = false;
	this->nas = false;
	this->vykresleno = false;

	//okno
	this->nastaveniOkna();

	//text
	this->nastaveniFont();
	this->nastaveniText();
}

Hra::~Hra() {
	delete this->okno;

	if (this->hra_zacala) {
		for (int i = 0; i < this->velikost; i++) {
			delete[] this->tlacitka[i];
		}
		delete tlacitka;
	}
}

//--------------------------------------------------------------------------------------------------------------------

//funkce pro konstruktor
void Hra::nastaveniOkna() {
	this->video.height = 900;
	this->video.width = 1600;

	this->okno = new sf::RenderWindow(sf::VideoMode(this->video.width, this->video.height), "Piskvorky", sf::Style::Close | sf::Style::Titlebar);

	this->okno->setFramerateLimit(60);
}

void Hra::nastaveniFont() {
	if (!this->font.loadFromFile("Fonts/Roboto-Black.ttf")) {
		std::cout << "ERROR::INITFONT::Failde to load font!" << std::endl;
	}
}

void Hra::nastaveniText() {
	this->text.setFont(this->font);
	this->text.setCharacterSize(18);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("");
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

void Hra::menu() {
	this->zacit_hru.setVelikost(100, 50);
	this->zacit_hru.setBarvuPozadi(sf::Color::Green);
	this->zacit_hru.setBarvaTextu(sf::Color::Black);
	this->zacit_hru.setSouradnice(this->okno->getSize().x / 2 - 50, this->okno->getSize().y / 2 - 100);
	this->zacit_hru.setText("Zacit hru");

	if (this->zacit_hru.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->zacit_hru.zmacknuto && !this->nas && !this->hra_zacala){
		this->hra_zacala = true;
		this->zacit_hru.zmacknuto = true;
		this->jednou = false;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->zacit_hru.zmacknuto = false;
	}

	this->nastaveni.setVelikost(100, 50);
	this->nastaveni.setBarvuPozadi(sf::Color::Green);
	this->nastaveni.setBarvaTextu(sf::Color::Black);
	this->nastaveni.setSouradnice(this->okno->getSize().x / 2 - 50, this->okno->getSize().y / 2 - 25);
	this->nastaveni.setText("Nastaveni");

	if (this->nastaveni.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->nastaveni.zmacknuto && !this->nas && !this->hra_zacala) {
		this->nas = true;
		this->nastaveni.zmacknuto = true;
		this->setVyhru.zmacknuto = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->nastaveni.zmacknuto = false;
	}
}

void Hra::funkceNastaveni() {
	this->setVelikost.setVelikost(200, 50);
	this->setVelikost.setBarvuPozadi(sf::Color::Green);
	this->setVelikost.setBarvaTextu(sf::Color::Black);
	this->setVelikost.setSouradnice(this->okno->getSize().x / 2 - 100, this->okno->getSize().y / 2 - 100);
	std::string vel = std::to_string(this->velikost);
	this->setVelikost.setText("Velikost pole " + vel);

	if (this->setVelikost.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->setVelikost.zmacknuto) {
		if(this->velikost < 15)
			this->velikost++;
		std::string vel = std::to_string(this->velikost);
		this->setVelikost.setText("Velikost pole " + vel);
		this->setVelikost.render(this->okno);
		this->setVelikost.zmacknuto = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->setVelikost.zmacknuto = false;
	}
	if (this->setVelikost.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !this->setVelikost.pravy_zmacknuto) {
		if (this->velikost > this->na_vyhru)
			this->velikost--;
		std::string vel = std::to_string(this->velikost);
		this->setVelikost.setText("Velikost pole " + vel);
		this->setVelikost.render(this->okno);
		this->setVelikost.pravy_zmacknuto = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->setVelikost.pravy_zmacknuto = false;
	}

	this->setVyhru.setVelikost(200, 50);
	this->setVyhru.setBarvuPozadi(sf::Color::Green);
	this->setVyhru.setBarvaTextu(sf::Color::Black);
	this->setVyhru.setSouradnice(this->okno->getSize().x / 2 - 100, this->okno->getSize().y / 2 - 25);
	std::string nas = std::to_string(this->na_vyhru);
	this->setVyhru.setText("Pocet na vyhru " + nas);

	if (this->setVyhru.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->setVyhru.zmacknuto) {
		if (this->na_vyhru < 6)
			this->na_vyhru++;
		std::string vel = std::to_string(this->velikost);
		this->setVyhru.setText("Velikost pole " + vel);
		this->setVyhru.render(this->okno);
		this->setVyhru.zmacknuto = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->setVyhru.zmacknuto = false;
	}
	if (this->setVyhru.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !this->setVyhru.pravy_zmacknuto) {
		if (this->na_vyhru > 2)
			this->na_vyhru--;
		std::string vel = std::to_string(this->velikost);
		this->setVyhru.setText("Velikost pole " + vel);
		this->setVyhru.render(this->okno);
		this->setVyhru.pravy_zmacknuto = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->setVyhru.pravy_zmacknuto = false;
	}

	this->back.setVelikost(80, 30);
	this->back.setBarvuPozadi(sf::Color::Green);
	this->back.setBarvaTextu(sf::Color::Black);
	this->back.setSouradnice(this->okno->getSize().x / 2 - 200, this->okno->getSize().y / 2 + 50);
	this->back.setText("Zpatky");

	if (this->back.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->nas = false;
	}
}

void Hra::exit() {
	this->konec.setVelikost(80, 30);
	this->konec.setBarvuPozadi(sf::Color::Green);
	this->konec.setBarvaTextu(sf::Color::Black);
	this->konec.setSouradnice(this->okno->getSize().x - 85, 5);
	this->konec.setText("Ukoncit");

	if (this->konec.tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->okno->close();
	}
}

void Hra::render() {
	this->okno->display();
	if (!this->hra_zacala && !this->nas) {
		this->okno->clear(sf::Color::Blue);
		this->zacit_hru.render(this->okno);
		this->nastaveni.render(this->okno);
	}
	else if (this->nas) {
		this->okno->clear(sf::Color::Blue);
		this->setVelikost.render(this->okno);
		this->setVyhru.render(this->okno);
		this->back.render(this->okno);
	}
	else if(this->hra_zacala){
		this->okno->clear(sf::Color::White);
		this->renderPole();
	}
	this->konec.render(this->okno);
}

void Hra::renderPole() {
	for (int i = 0; i < this->velikost; i++) {
		for (int j = 0; j < this->velikost; j++) {
			this->tlacitka[i][j].render(this->okno);
		}
	}
}

void Hra::update() {
	this->exit();
	this->menu();
	this->kurzorUpdate();
	this->eventLoop();
	if (!this->vykresleno && this->hra_zacala) {
		this->vykresleniPole(this->velikost);
		this->vykresleno = true;
	}
	if (this->nas) {
		this->funkceNastaveni();

	}
	if (this->hra_zacala) {
		this->updatePole();
	}
}

void Hra::updatePole() {
	for (int i = 0; i < this->velikost; i++) {
		for (int j = 0; j < this->velikost; j++) {
			if (this->tlacitka[i][j].tvar.getGlobalBounds().contains(this->pozice_kurzoru) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->tlacitka[i][j].zmacknuto
				&& this->jednou && !this->vyhrano && !this->nas && this->hra_zacala) {
				vyplneniPole(j, i);
				this->tlacitka[i][j].zmacknuto = true;
				this->jednou = false;
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->tlacitka[i][j].zmacknuto = false;
				this->jednou = true;
			}
		}
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

void Hra::vykresleniPole(int velikost) {
	float zacatekX = ((this->okno->getSize().x - (50 * velikost)) / 2) - 25;
	float zacatekY = ((this->okno->getSize().y - (50 * velikost)) / 2) - 25;
	this->velikost = velikost;
	this->tlacitka = new Tlacitko*[velikost];
	for (int i = 0; i < velikost; i++) {
		this->tlacitka[i] = new Tlacitko[velikost];
	}
	float x = zacatekX;
	float y = zacatekY;
	for (int i = 0; i < velikost; i++) {
		for (int j = 0; j < velikost; j++) {
			this->tlacitka[i][j].setSouradnice(x , y);
			x += 55;
		}
		x = zacatekX;
		y += 55;
	}
}

void Hra::vyplneniPole(int x, int y) {
	std::string znak;
	if (this->tlacitka[y][x].getText() == "") {
		for (int i = 0; i < this->velikost; i++) {
			for (int j = 0; j < this->velikost; j++) {
				this->tlacitka[i][j].setBarvaTextu(sf::Color::White);
			}
		}
		if (this->tah % 2 == 0) {
			znak = "X";
			this->tlacitka[y][x].setText(znak);
		}
		else {
			znak = "O";
			this->tlacitka[y][x].setText(znak);
		}

		this->tah++;

		//volani vyher
		if (this->vodorovne(x, y, znak)) {
			std::cout << "Vyhral " << znak << std::endl;
		}
		else if (this->svisle(x, y, znak)) {
			std::cout << "Vyhral " << znak << std::endl;
		}
		else if (this->sikmo1(x, y, znak)) {
			std::cout << "Vyhral " << znak << std::endl;
		}
		else if (this->sikmo2(x, y, znak)) {
			std::cout << "Vyhral " << znak << std::endl;
		}
	}
	else {
		this->tlacitka[y][x].setBarvaTextu(sf::Color::Red);
	}
}

//vyhry
bool Hra::vodorovne(int _x, int _y, std::string znak) {
	int pocet = 0;
	int x = _x;
	int y = _y;
	
	for (int i = 0; i < this->na_vyhru; i++) {
		if (x < this->velikost) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		x++;
	}
	x = _x - 1;
	for (int i = 0; i < this->na_vyhru; i++) {
		if (x >= 0) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		x--;
	}
	if (pocet >= this->na_vyhru) {
		this->vyhrano = true;
		return true;
	}
	else {
		for (int i = 0; i < this->velikost; i++) {
			for (int j = 0; j < this->velikost; j++) {
				this->tlacitka[i][j].tvar.setFillColor(sf::Color::Blue);
			}
		}
		return false;
	}
}

bool Hra::svisle(int _x, int _y, std::string znak) {
	int pocet = 0;
	int x = _x;
	int y = _y;

	for (int i = 0; i < this->na_vyhru; i++) {
		if (y < this->velikost) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		y++;
	}
	y = _y - 1;
	for (int i = 0; i < this->na_vyhru; i++) {
		if (y >= 0) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		y--;
	}
	if (pocet >= this->na_vyhru) {
		this->vyhrano = true;
		return true;
	}
	else {
		for (int i = 0; i < this->velikost; i++) {
			for (int j = 0; j < this->velikost; j++) {
				this->tlacitka[i][j].tvar.setFillColor(sf::Color::Blue);
			}
		}
		return false;
	}
}

bool Hra::sikmo1(int _x, int _y, std::string znak) {
	int pocet = 0;
	int x = _x;
	int y = _y;

	for (int i = 0; i < this->na_vyhru; i++) {
		if (x < this->velikost && y < this->velikost) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		x++;
		y++;
	}
	x = _x - 1;
	y = _y - 1;
	for (int i = 0; i < this->na_vyhru; i++) {
		if (x >= 0 && y >= 0) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		x--;
		y--;
	}
	if (pocet >= this->na_vyhru) {
		this->vyhrano = true;
		return true;
	}
	else {
		for (int i = 0; i < this->velikost; i++) {
			for (int j = 0; j < this->velikost; j++) {
				this->tlacitka[i][j].tvar.setFillColor(sf::Color::Blue);
			}
		}
		return false;
	}
}

bool Hra::sikmo2(int _x, int _y, std::string znak) {
	int pocet = 0;
	int x = _x;
	int y = _y;

	for (int i = 0; i < this->na_vyhru; i++) {
		if (x < this->velikost && y >= 0) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		x++;
		y--;
	}
	x = _x - 1;
	y = _y + 1;
	for (int i = 0; i < this->na_vyhru; i++) {
		if (x >= 0 && y < this->velikost) {
			if (this->tlacitka[y][x].getText() == znak) {
				pocet++;
				this->tlacitka[y][x].tvar.setFillColor(sf::Color::Green);
			}
			else {
				break;
			}
		}
		x--;
		y++;
	}
	if (pocet >= this->na_vyhru) {
		this->vyhrano = true;
		return true;
	}
	else {
		for (int i = 0; i < this->velikost; i++) {
			for (int j = 0; j < this->velikost; j++) {
				this->tlacitka[i][j].tvar.setFillColor(sf::Color::Blue);
			}
		}
		return false;
	}
}

//--------------------------------------------------------------------------------------------------------------------

//gettery
bool Hra::running(){
	return this->okno->isOpen();
}