#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include "Kostka.h"
#include "Interakce.h"
#include "Bojovnici.h"
#include "Souboj.h"

using namespace std;

int main() {
	Interakce hrac1, hrac2;

	Souboj souboj;
	
	//Kostka kostka;

	//kostka.pocet_sten_kostky();

	hrac1.zalozeni_hrace(1);	//zadani jmena hrace

	

	hrac1.vyber_postavu();	//tady si hrac vybere postavu

	

	hrac2.zalozeni_hrace(2);



	hrac2.vyber_postavu();

	souboj.vypis_bitvy(hrac1.hrac, hrac2.hrac);

	

	return 0;
}