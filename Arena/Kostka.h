#ifndef __KOSTKA_H_
#define __KOSTKA_H_
#include <iostream>
#include <stdlib.h>
#include <ctime>

#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */


using namespace std;

class Kostka{
public:
	//void pocet_sten_kostky();
	//char nacteni;
	const int pocet_sten = 6;
	int hod();
};

#endif