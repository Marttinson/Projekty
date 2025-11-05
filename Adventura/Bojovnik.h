#pragma once
#include <iostream>
#include <string>

using namespace std;

class Bojovnik
{
public:
	string nazev;
	int obrana;
	int utok;
	int hp;
	string vyber;
	void vypisTrid();
	void urceniTridy();
	void valecnik();
	void lukostrelec();
	void kouzelnik();
};

