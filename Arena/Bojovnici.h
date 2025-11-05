#ifndef __BOJOVNICI_H_
#define __BOJOVNICI_H_
#include <string>

using namespace std;

class Bojovnici {
public:
	int max_hp;
	int hp;
	int dmg;
	int obrana;
	string jmeno;
	void Valecnik();
	void Kouzelnik();
	void Lovec();
};

#endif