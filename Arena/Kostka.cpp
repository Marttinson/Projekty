#include "Kostka.h"

/*void Kostka::pocet_sten_kostky() {	//zadani hrace pocet sten kostky
	sem:
	cout << BOLDWHITE << "S kolikati hranou kostkou chcete hrat?	";
	cin >> this->nacteni;
	cout << RESET;

	if (nacteni >= '1' && nacteni <= '9') {
		this->pocet_sten = nacteni - '0';
		cout << endl;
		cout << this->pocet_sten;
	}
	else {
		cout << BOLDRED << "Neplatna hodnota" << RESET << endl;
		goto sem;
	}
}*/

int Kostka::hod(){
	return 1 + rand() % this->pocet_sten;
}