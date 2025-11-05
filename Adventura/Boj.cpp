#include "Boj.h"

void Boj::Cezhar() {
	cout << "\nUtkas se s mocnym Cezharem\n";
	this->jmeno = "Cezhar";
	this->hp = 100;
	this->dmg = 10;
	this->odmena_za_zabiti = 1000;
}

void Boj::Glum() {
	cout << "\nPotkal si ohavneho gluma\n";
	this->jmeno = "Glum";
	this->hp = 20;
	this->dmg = 5;
	this->odmena_za_zabiti = 10;
}

void Boj::souboj(string souper) {
	if (souper == "Cezhar")
		this->Cezhar();
	else if (souper == "Glum") 
		this->Glum();

	cout << "HP: " << this->hp << endl << "Utok: " << this->dmg << endl << "Odmena za zabiti: " << this->odmena_za_zabiti << endl;
	
	char vyber;
	cout << "1. dat se na utek\n2. utkat se s " << this->jmeno << endl;
	cin >> vyber;

	if (vyber == '1') {
		int random;
		random = randomCislo(5);

		if (random == 1) {
			cout << "Utek se nezdaril zemrel si\n";
			hrac.bojovnik.hp = 0;
		}
		else {
			cout << "Uspesne si utekl\n";
		}
	}
	else if (vyber == '2') {
		
	}
}