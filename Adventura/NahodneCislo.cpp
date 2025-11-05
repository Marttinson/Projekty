#include "NahodneCislo.h"

int NahodneCislo::randomCislo(int rozsah) {
	return (rand() % rozsah) + 1;
}