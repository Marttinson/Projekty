#include "Hra.h"

void Hra::vypisMenu() {
	cout << endl << hrac.bojovnik.nazev << " " << hrac.jmeno << endl;
	cout << "Uroven: " << hrac.level << endl;
	cout << "Zlato: " << hrac.zlato << endl << endl;

	mapa.vypisMapy();

	cout << "\nVyber interakce:\n";
	cout << "1.Pohyb po mape\n";
	cout << "2.Inventar\n";
	cout << "3.Vysvetlivky\n";
	cin >> this->vyber;
	cout << "\n\n";

	if (this->vyber == "1" || this->vyber == "Pohyb" || this->vyber == "pohyb") {
		cout << "Vyber si smer pohybu\n";
		cout << "1.Do prava\n2.Do leva\n3.Nahoru\n4.Dolu\n\n";

		string vyber_pohybu;
		cin >> vyber_pohybu;

		mapa.pohyb(vyber_pohybu);
		
		interakce();
		
	}
	else if (this->vyber == "2" || this->vyber == "Inventar" || this->vyber == "inventar") {
		hrac.Inventar::vypisInventare();
	}
	else if (this->vyber == "3" || this->vyber == "Vysvetlivky" || this->vyber == "vysvetlivky") {
		this->vysvetlivky();
	}
	if (hrac.bojovnik.hp > 0) {
		cout << endl;
		system("pause");
	}
}

void Hra::uvitani() {
	cout << "Jestli si pripraven projit si tim nejvetsim dobrodruzstvim zadej sve jmeno\n";
	cin >> hrac.jmeno;

	cout << "Ted kdyz uz vim s kym mam tu cest mi rekni jakemu stylu boje se venujes\n";
	hrac.bojovnik.urceniTridy();
	cout << "Vyborne, ale rekl bych ze se musis jeste hodne zlepsit, tak se do toho dej\n\n";

	mapa.naplneniMapy();
	
	this->vypisMenu();
}

void Hra::hraj() {
	this->uvitani();
	while (hrac.bojovnik.hp > 0) {
		cout << "\n\n\n\n--------------------------------------------------------------\n\n\n\n";
		vypisMenu();
	}
	cout << "\nHra skoncila\n";
}

void Hra::vysvetlivky() {
	cout << "Nic - mas smulu, na policku nic nic neni\n";
	cout << "Obchodnik - muzes si u nej koupit nebo prodat nejake vybaveni\n";
	cout << "Loot - na tomto policku se nachazi nejake vybaveni\n";
}

void Hra::interakce() {
	mapa.vymazaniMezer();
	if (mapa.policko_hrace == "Nic") {
		cout << "\nNa tomto policku se nic nedeje\n";
	}
	else if (mapa.policko_hrace == "Obchodnik") {
		cout << "\nVesel si k obchodnikovi\n";
	}
	else if (mapa.policko_hrace == "Loot") {
		cout << "\nNasel si poklad\n";
		hrac.loot();
	}
	else if (mapa.policko_hrace == "Cezhar") {
		Boj::souboj("Cezhar");
	}
	else if (mapa.policko_hrace == "Glum") {
		Boj::souboj("Glum");
	}
}