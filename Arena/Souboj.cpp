#include "Souboj.h"

void Souboj::bitva(Hrac &hrac1, Hrac &hrac2) {
	
	this->hod_hrace1 = kostka1.hod();
	this->hod_hrace2 = kostka2.hod();
	
	cout << BOLDCYAN << hrac1.jmeno << " hodil " << hod_hrace1 << " k obrane." << RESET << endl;
	cout << BOLDCYAN << hrac2.jmeno << " hodil " << hod_hrace2 << " k obrane." << RESET << endl << endl;
	
	this->obrana_hrace1 = hrac1.bojovnik.obrana + this->hod_hrace1;
	this->obrana_hrace2 = hrac2.bojovnik.obrana + this->hod_hrace2;
	
	cout << BOLDBLUE << "Celkova obrana hrace " << hrac1.jmeno << " je: " << obrana_hrace1 << RESET << endl;
	cout << BOLDBLUE << "Celkova obrana hrace " << hrac2.jmeno << " je: " << obrana_hrace2 << RESET << endl << endl;

	this->hod_hrace1 = kostka1.hod();
	this->hod_hrace2 = kostka2.hod();
	
	cout << BOLDCYAN << hrac1.jmeno << " hodil " << hod_hrace1 << " k utoku." << RESET << endl;
	cout << BOLDCYAN << hrac2.jmeno << " hodil " << hod_hrace2 << " k utoku." << RESET << endl << endl;
	
	this->poskozeni_hrace1 = hrac1.bojovnik.dmg + this->hod_hrace1 - obrana_hrace2;
	this->poskozeni_hrace2 = hrac2.bojovnik.dmg + this->hod_hrace2 - obrana_hrace1;

	

	if (this->poskozeni_hrace1 > 0) 
		hrac2.bojovnik.hp -= this->poskozeni_hrace1;
	else
		this->poskozeni_hrace1 = 0;
	
	if (this->poskozeni_hrace2 > 0) 
		hrac1.bojovnik.hp -= this->poskozeni_hrace2;
	else
		this->poskozeni_hrace2 = 0;
	
	cout << BOLDRED << "Poskozeni, ktere zpusobi hrac " << hrac1.jmeno << ": " << poskozeni_hrace1 << RESET << endl;
	cout << BOLDRED << "Poskozeni, ktere zpusobi hrac " << hrac2.jmeno << ": " << poskozeni_hrace2 << RESET << endl << endl;
}

void Souboj::vypis_bitvy(Hrac &hrac1, Hrac &hrac2) {

	while (hrac1.bojovnik.hp > 0 && hrac2.bojovnik.hp > 0) {
		
		bitva(hrac1, hrac2);

		cout << BOLDWHITE << "Hrac " << hrac1.jmeno << " hp: " << hrac1.bojovnik.hp << RESET << endl;

		cout << BOLDWHITE << "Hrac " << hrac2.jmeno << " hp: " << hrac2.bojovnik.hp << RESET << endl << endl;

		cout << BOLDYELLOW << "---------------------------------------" << RESET << endl << endl;
		
	}
	if (hrac1.bojovnik.hp == hrac2.bojovnik.hp)
		cout << BOLDGREEN << "Plichta" << RESET;
	else if (hrac1.bojovnik.hp > hrac2.bojovnik.hp)
		cout << BOLDGREEN << "Vitezem je hrac " << hrac1.jmeno << " s hp: " << hrac1.bojovnik.hp << RESET;
	else
		cout << BOLDGREEN << "Vitezem je hrac " << hrac2.jmeno << " s hp: " << hrac2.bojovnik.hp << RESET;
}