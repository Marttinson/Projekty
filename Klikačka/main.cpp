#include "Hra.h"

int main() {
	srand(time(NULL));

	Hra hra;

	//Game loop
	while (hra.running() && !hra.getEndGame()) {

		//Update
		hra.update();

		//Render
		hra.render();

	}

	return 0;
}