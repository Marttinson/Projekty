#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// aritmeticka posloupnost
// vypocet n prvku pomoci 1. prvku
void vypocet_n_clenu(double a1, double d1, double d2, int n) { //hodnota 1. prvku posloupnosti, citatel diference, jmenovatel diference, pocet prvku k vypocitani
	double soucet = a1;
	cout << "a1: " << a1 << endl;
	for (int i = 0; i < n; i++) {
		a1 += (d1/d2);
		cout << "a" << i + 2 << ": " << a1 << endl;
		soucet += a1;
	}
}

// vypocet nteho clene pomoci libovolneho prvku
void vypocet_n_clene(double a, double d1, double d2, int n, int nty) { //hodnota znameho prvku posloupnosti, citatel diference, jmenovatel diference, pocet prvku k vypocitani, poradi znameho prvku
	if (n > nty) {
		for (int i = nty; i < n; i++) {
			a += (d1 / d2);
		}
	}
	else {
		for (int i = nty; i > n; i--) {
			a -= (d1 / d2);
		}
	}
	cout << "a" << n << ": " << a << endl;
}
//---------------------------------------------------------------------- geometricka posloupnost -------------------------------------------------------------------
//vypocet libovolneho poctu prvku pomoci q a a1 + soucet jejich prvku
void vypocitani_an(double a1, double q1, double q2, int n) { //hodnota 1. prvku, citatel q, jmenovatel q, pocet prvku k vypocitani
	double soucet = a1;
	for (int i = 0; i < n; i++) {
		a1 *= (q1 / q2);
		cout << "a" << i + 2 << ": " << a1 << endl;
		soucet += a1;
	}
	cout << "Soucet techto prvku je: " << soucet << endl;
}

//vypocet libovolneho poctu prvku pomoci q a libovolneho prvku + soucet techto prvku
void vypocet_n_prvku(int nty, double an, double q1, double q2, int n) {	//poradi znameho prvku, hodnota znameho prvku, citatel q, jmenovatel q, pocet prvku k vypocitani
	for (int i = nty; i > 1; i--) {
		an /= (q1 / q2);
	}

	cout << "a1: " << an << endl;
	double soucet = an;
	for (int i = 0; i < n - 1; i++) {
		an *= (q1 / q2);
		cout << "a" << i + 2 << ": " << an << endl;
		soucet += an;
	}
	cout << "Soucet techto prvku je: " << soucet << endl;
}

//vypocet libovolneho poctu prvku se sousednimi prvky a neznamou q
void vypocet_bez_q(double an1, double an2, int nty1, int nty2, int n) {	//hodnota 1. znameho prvku, hodnota 2. znameho prvku, poradi 1. znameho prvku1 poradi 2. znameho prvku, pocet prvku k vypocitani
	double q;

	q = an2 / an1;

	for (int i = nty1; i > 1; i--) {
		an1 /= q;
	}
	cout << "q: " << q << endl;

	cout << "a1: " << an1 << endl;

	for (int i = 0; i < n - 1; i++) {
		an1 *= q;
		cout << "a" << i + 2 << ": " << an1 << endl;
	}
}

//vypocet libovolneho poctu prvku pomoci libovolnych dvou prvku, bez q
void vypocet_pomoci_libovolnych_prvku(double a11, double a12, int nty1, double a21, double a22, int nty2, int n) { //hodnota 1. znameho prvku, poradi tohoto prvku, hodnota 2. znameho prvku, poradi tohoto prvku, pocet prvku k vypocitani
	double a = a11 / a12;
	double q = pow((a21 / a22) / (a11 / a12), 1.0 / (nty2 - nty1));

	for (int i = nty1; i > 1; i--) {
		a /= q;
	}

	double soucet = a;

	cout << "q: " << q << endl;
	cout << "a1: " << a << endl;

	for (int i = 0; i < n - 1; i++) {
		a *= q;
		cout << "a" << i + 2 << ": " << a << endl;
		soucet += a;
	}
	cout << "Soucet techto prvku je: " << soucet << endl;
}

int main(void) {
	double a1;
	double q1, q2;
	int n;
	int nty, nty2;
	int vyber1, vyber2, vyber3;
	double an, an2;

	cout << "Vyber si jednu moznost." << endl << "1.Aritmeticka posloupnost." << endl << "2.Geometricka posloupnost" << endl;
	cin >> vyber1;
	cout << "-------------------------------------------------" << endl;

	if (vyber1 == 1) {
		cout << "Vyber si jednu z mounosti." << endl << "1.Vypocet posloupnosti o n delce." << endl << "2.Vypocet n prvku." << endl;
		cin >> vyber2;
		cout << "-------------------------------------------------" << endl;

		if (vyber2 == 1) {
			double a1;
			double d1, d2;

			cout << "Zadej 1. prvek posloupnosti: ";
			cin >> a1;

			cout << "Zadej citatel diference (d): ";
			cin >> d1;

			cout << "Zadej jmenovatel diference (d): ";
			cin >> d2;

			cout << "Zadej kolik prvku chces spocitat: ";
			cin >> n;

			vypocet_n_clenu(a1, d1, d2, n);
		}

		else if (vyber2 == 2) {
			double a;
			double d1, d2;

			cout << "Zadej kolikaty prvek znas: ";
			cin >> nty;

			cout << "Zadej hodnotu tohoto prvku: ";
			cin >> a;

			cout << "Zadej citatel diference (d): ";
			cin >> d1;

			cout << "Zadej jmenovatel diference (d): ";
			cin >> d2;

			cout << "Zadej kolikaty prvek chces vypocitat: ";
			cin >> n;

			vypocet_n_clene(a, d1, d2, n, nty);
		}
		else
			cout << "Neplatna volba.";
	}

	else if (vyber1 == 2) {
		cout << "Vyber si jednu z moznosti." << endl << "1.Vypocet n prvku pomoci q a a1 + jejich soucet." << endl << "2.Vypocet n prvku se znamou q a libovolnym prvkem + jejich soucet." << endl << "3.Vypocet n prvku se sousednimi prvky a neznamou q." << endl << "4.Vypocet n prvku pomoci libovolnych dvou prvku, jejich soucet a q." << endl;
		cin >> vyber3;
		cout << "-------------------------------------------------" << endl;

		if (vyber3 == 1) {
			cout << "Zadej a1: ";
			cin >> a1;

			cout << "Zadej citatel q: ";
			cin >> q1;

			cout << "Zadej jmenovatel q: ";
			cin >> q2;

			cout << "Zadej kolik prvku chces vypocitat: ";
			cin >> n;

			vypocitani_an(a1, q1, q2, n);
		}
		else if (vyber3 == 2) {

			cout << "Zadej kolikaty prvek znas: ";
			cin >> nty;

			cout << "Zadej hodnotu tohoto prvku: ";
			cin >> an;

			cout << "Zadej citatel q: ";
			cin >> q1;

			cout << "Zadej jmenovatel q: ";
			cin >> q2;

			cout << "Zadej kolik prvku chces vypocitat: ";
			cin >> n;

			vypocet_n_prvku(nty, an, q1, q2, n);

		}
		else if (vyber3 == 3) {

			cout << "Zadane prvku musi byt sousedici!!!" << endl;

			cout << "Zadej poradi 1. prvku ktery znas: ";
			cin >> nty;

			cout << "Zadej hodnotu tohoto prvku: ";
			cin >> an;

			cout << "Zadej poradi 2. prvku ktery znas: ";
			cin >> nty2;

			cout << "Zadej hodnotu tohoto prvku: ";
			cin >> an2;

			cout << "Zadej kolik prvku chces vypocitat: ";
			cin >> n;

			vypocet_bez_q(an, an2, nty, nty2, n);
		}
		else if (vyber3 == 4) {
			int nty1, nty2;
			double a11, a12, a21, a22;
			int n;

			cout << "Zadej hodnotu citatele 1. prvku: ";
			cin >> a11;

			cout << "Zadej hodnotu jmenovatele 1. prvku: ";
			cin >> a12;
			
			cout << "Zadej poradi tohoto prvku: ";
			cin >> nty1;

			cout << "Zadej hodnotu citatele 2. prvku: ";
			cin >> a21;

			cout << "Zadej hodnotu jmenovatele 2. prvku: ";
			cin >> a22;

			cout << "Zadej poradi tohoto prvku: ";
			cin >> nty2;

			cout << "Zadej kolik prvku chces vypocitat: ";
			cin >> n;

			vypocet_pomoci_libovolnych_prvku(a11, a12, nty1, a21, a22, nty2, n);
		}
		else
			cout << "Neplatna volba.";
	}
	else
		cout << "Neplatna volba.";

	return 0;
}