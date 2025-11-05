#pragma once
#include "Mapa.h"
#include "Boj.h"

class Hra : public Boj
{
public:
	Mapa mapa;
	string vyber;
	void hraj();
	void uvitani();
	void vypisMenu();
	void vysvetlivky();
	void interakce();
};

