#include "Interakce.h"

void Interakce::zalozeni_hrace(int i) {
	cout << BOLDWHITE << "Zadej jmeno " << i << ". hrace: " << RESET;
	cout << BOLDMAGENTA;
	cin >> hrac.jmeno;
	cout << RESET;
}

/*void Interakce::pocet_sten_kostky(Kostka &kostka) {	//zadani hrace pocet sten kostky
	cout << "S kolikati hranou kostkou chcete hrat?" << endl;
	cin >> kostka.pocet_sten;
}*/

void Interakce::vyber_postavu() {	//Vyber postavy
	sem:
	cout << BOLDWHITE << "Hraci " << BOLDMAGENTA << hrac.jmeno << BOLDWHITE << " vyber si jednu z postav:" << RESET << endl;

	hrac.bojovnik.Valecnik();
	cout << BOLDYELLOW << hrac.bojovnik.jmeno << ": " << BOLDGREEN << "hp: " << hrac.bojovnik.hp << BOLDCYAN << " obrana: " << hrac.bojovnik.obrana << BOLDRED << " utok " << hrac.bojovnik.dmg << RESET << endl;

	hrac.bojovnik.Lovec();
	cout << BOLDYELLOW << hrac.bojovnik.jmeno << ": " << BOLDGREEN << "hp: " << hrac.bojovnik.hp << BOLDCYAN << " obrana: " << hrac.bojovnik.obrana << BOLDRED << " utok " << hrac.bojovnik.dmg << RESET << endl;

	hrac.bojovnik.Kouzelnik();
	cout << BOLDYELLOW << hrac.bojovnik.jmeno << ": " << BOLDGREEN << "hp: " << hrac.bojovnik.hp << BOLDCYAN << " obrana: " << hrac.bojovnik.obrana << BOLDRED << " utok " << hrac.bojovnik.dmg << RESET << endl;
	cout << BOLDYELLOW;
	cin >> hrac.bojovnik.jmeno;
	cout << RESET;

	if (hrac.bojovnik.jmeno == "Valecnik" || hrac.bojovnik.jmeno == "valecnik" || hrac.bojovnik.jmeno == "VALECNIK") {
		hrac.bojovnik.Valecnik();
		cout << BOLDWHITE << "Vybral si si " << BOLDYELLOW << hrac.bojovnik.jmeno << RESET << endl;
	}
	else if (hrac.bojovnik.jmeno == "Lovec" || hrac.bojovnik.jmeno == "lovec" || hrac.bojovnik.jmeno == "LOVEC") {
		hrac.bojovnik.Lovec();
		cout << BOLDWHITE << "Vybral si si " << BOLDYELLOW << hrac.bojovnik.jmeno << RESET << endl;
	}
	else if (hrac.bojovnik.jmeno == "Kouzelnik" || hrac.bojovnik.jmeno == "kouzelnik" || hrac.bojovnik.jmeno == "KOUZELNIK") {
		hrac.bojovnik.Kouzelnik();
		cout << BOLDWHITE << "Vybral si si " << BOLDYELLOW << hrac.bojovnik.jmeno << RESET << endl;
	}
	else {
		cout << BOLDRED << "Neplatna hodnota." << RESET << endl << endl;
		goto sem;
	}

	cout << BOLDYELLOW << "---------------------------------------" << RESET << endl;
}