#include "Mapa.h"

void Mapa::vypisMapy() {
	this->vyrovnani();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++)
			cout << pole[i][j];
		cout << endl;
	}
}

void Mapa::naplneniMapy() {
	int j = 0;
	int k = 0;
	for (int i = 0; i < 15; i++) {
		int random = randomCislo(this->rozsah_nahodneho_cisla);
		if (k == 5) {
			k = 0;
			j++;
		}

		if (random <= 2)
			pole[j][k] = "Obchodnik";
		else if (random <= 4)
			pole[j][k] = "Loot";
		else if (random <= 10)
			pole[j][k] = "Nic";


		k++;
	}

	for (int i = 0; i < 3; i++) {
		this->pole[i][1] = "  |  ";
		this->pole[i][3] = "  |  ";
	}

	this->pole[1][2] =  "HRAC";

	//this->vypisMapy();
}

void Mapa::vyrovnani() {
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 5; k++) {
			if (this->max < pole[j][k].length()) 
				this->max = pole[j][k].length();
		}
	}

	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 5; k++) {
			if (k != 1 && k != 3) {
				for (size_t i = pole[j][k].length(); i < this->max; i++) {
					pole[j][k].push_back(' ');
				}
			}
		}
	}
}

void Mapa::pohyb(string smer) {
	if (smer == "1" || smer == "P" || smer == "p") {
		this->policko_hrace = pole[1][4];

		pole[0][0] = pole[0][2];
		pole[1][0] = "Nic";
		pole[2][0] = pole[2][2];

		pole[0][2] = pole[0][4];
		pole[1][2] = "HRAC";
		pole[2][2] = pole[2][4];

		for (int i = 0; i < 3; i++)
			pole[i][4] = naplneniPolicka();
	}
	else if (smer == "2" || smer == "L" || smer == "l") {
		this->policko_hrace = pole[1][0];

		pole[0][4] = pole[0][2];
		pole[1][4] = "Nic";
		pole[2][4] = pole[2][2];

		pole[0][2] = pole[0][0];
		pole[1][2] = "HRAC";
		pole[2][2] = pole[2][0];

		for (int i = 0; i < 3; i++)
			pole[i][0] = naplneniPolicka();
	}
	else if (smer == "3" || smer == "H" || smer == "h") {
		this->policko_hrace = pole[0][2];

		pole[2][0] = pole[1][0];
		pole[2][2] = "Nic";
		pole[2][4] = pole[1][4];

		pole[1][0] = pole[0][0];
		pole[1][2] = "HRAC";
		pole[1][4] = pole[0][4];

		
		pole[0][0] = naplneniPolicka();
		pole[0][2] = naplneniPolicka();
		pole[0][4] = naplneniPolicka();
	}
	else if (smer == "4" || smer == "D" || smer == "d") {
		this->policko_hrace = pole[2][2];

		pole[0][0] = pole[1][0];
		pole[0][2] = "Nic";
		pole[0][4] = pole[1][4];

		pole[1][0] = pole[2][0];
		pole[1][2] = "HRAC";
		pole[1][4] = pole[2][4];


		pole[2][0] = naplneniPolicka();
		pole[2][2] = naplneniPolicka();
		pole[2][4] = naplneniPolicka();
	}
	//this->vypisMapy();
}

string Mapa::naplneniPolicka() {
	int random = randomCislo(this->rozsah_nahodneho_cisla);

	if (random <= 2)
		return  "Obchodnik";
	else if (random <= 4)
		return  "Loot";
	else if (random == 5)
		return "Cezhar";
	else if (random == 6)
		return "Glum";
	else
		return "Nic";
}

void Mapa::vymazaniMezer() {
	size_t j = 0;
	char pomoc[20];

	while (this->policko_hrace[j] != ' ') {
		pomoc[j] = this->policko_hrace[j];
		if (j == this->policko_hrace.length())
			break;
		j++;
	}

	this->policko_hrace = "";

	for (size_t i = 0; i < j; i++) {
		policko_hrace.push_back(pomoc[i]);
	}
}

