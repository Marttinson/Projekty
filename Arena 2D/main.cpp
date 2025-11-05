#include <iostream>
#include "Vypis_areny.h"

using namespace std;

int main() {
	Vypis_areny arena;

	arena.uvitani();

	arena.hrac1.zalozeniHrace(1);

	arena.hrac2.zalozeniHrace(2);

	arena.zalozeni(arena.hrac1, arena.hrac2);

	arena.vyberAkce(arena.hrac1, arena.hrac2);

	return 0;
}