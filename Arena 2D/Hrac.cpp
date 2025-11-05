#include "Hrac.h"

void Hrac::zalozeniHrace(int poradi) {
    this->poradi = poradi;

    cout << BOLDWHITE << "Zadej jmeno " << this->poradi << ". hrace: " << BOLDGREEN;
    cin >> jmeno;
    
    cout << BOLDWHITE << "Zadej znak pro svou postavu: " << BOLDCYAN;
    cin >> znak;

sem:
    cout << BOLDWHITE << "Vyber si z nasledujicich bojovniku:" << RESET << endl << endl;
    bojovnik.vypisValecnika();
    bojovnik.vypisLovce();
    bojovnik.vypisKouzelnika();
    cout << BOLDMAGENTA;
    cin >> vyber_bojovnika;
    cout << RESET;
    if (vyber_bojovnika == "Valecnik" || vyber_bojovnika == "valecnik" || this->vyber_bojovnika == "1") {
        bojovnik.Valecnik();
    }
    else if (vyber_bojovnika == "Lovec" || vyber_bojovnika == "lovec" || vyber_bojovnika == "2") {
        bojovnik.Lovec();
    }
    else if (vyber_bojovnika == "Kouzelnik" || vyber_bojovnika == "kouzelnik" || vyber_bojovnika == "3") {
    }
    else {
        cout << BOLDWHITE << "Neplatna hodnota." << RESET << endl;
        goto sem;
    }
    cout << BOLDWHITE << "Vybral si si " << bojovnik.jmeno << RESET << endl << endl;
}

void Hrac::utokNaHrace1(Hrac hrac1, Hrac hrac2) {
	srand((unsigned)time(NULL));

	int nahoda;

	nahoda = 1 + rand() % hrac2.bojovnik.kritik;
	//cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = hrac2.bojovnik.dmg * 2 - hrac1.bojovnik.obrana;
		cout << BOLDGREEN << "Hrac " << hrac2.jmeno << BOLDRED << " dal kriticky uder" << RESET << endl << endl;
	}
	else {
		this->poskozeni = hrac2.bojovnik.dmg - hrac1.bojovnik.obrana;
	}

	nahoda = 1 + rand() % hrac1.bojovnik.vyhnuti;
	//cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = 0;
		cout << BOLDGREEN << "Hrac " << hrac1.jmeno << BOLDGREEN << " se vyhnul" << RESET << endl << endl;
	}
	else {
		if (this->poskozeni > 0) {
			bojovnik.hp -= this->poskozeni;
		}
		else {
			this->poskozeni = 0;
		}
	}
	//cout << this->poskozeni << endl;
	//cout << bojovnik.hp;
}

void Hrac::utokNaHrace2(Hrac hrac1, Hrac hrac2) {
	srand((unsigned)time(NULL));

	int nahoda;

	nahoda = 1 + rand() % hrac1.bojovnik.kritik;
	//cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = hrac1.bojovnik.dmg * 2 - hrac2.bojovnik.obrana;
		cout << BOLDGREEN << "Hrac " << hrac1.jmeno << BOLDRED << " dal kriticky uder" << RESET << endl << endl;
	}
	else {
		this->poskozeni = hrac1.bojovnik.dmg - hrac2.bojovnik.obrana;
	}

	nahoda = 1 + rand() % hrac2.bojovnik.vyhnuti;
	//cout << nahoda << endl;
	if (nahoda == 1) {
		this->poskozeni = 0;
		cout << BOLDGREEN << "Hrac " << hrac2.jmeno << BOLDGREEN << " se vyhnul" << RESET << endl << endl;
	}
	else {
		if (this->poskozeni > 0) {
			bojovnik.hp -= this->poskozeni;
		}
		else {
			this->poskozeni = 0;
		}
	}
	//cout << this->poskozeni << endl;
	//cout << bojovnik.hp;
}

void Hrac::pauza() {
	bojovnik.hp += bojovnik.pauza;

	if (bojovnik.hp > bojovnik.max_hp) {
		bojovnik.hp = bojovnik.max_hp;
		cout << BOLDWHITE << "Mas uz plne zivoty" << RESET << endl;
	}
	else
		cout << BOLDWHITE << "Hrac " << BOLDGREEN << jmeno << BOLDWHITE << " ma " << bojovnik.hp << "hp" << RESET << endl;
}