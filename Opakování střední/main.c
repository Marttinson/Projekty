#include <stdio.h>
#include <string.h>

// fuknce k prikladu 21
int porovnaniCisel(int a, int b) {
	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
		return 0;
}

// fuknce k prikladu 22
int jeZaporne(int cislo) {
	if (cislo > 0)
		return 1;
	else if (cislo < 0)
		return -1;
	else
		return 0;
}

// fuknce k prikladu 23
int jeVelkaSamohlaska(char znak) {
	if (znak == 'A' || znak == 'E' || znak == 'I' || znak == 'O' ||
		znak == 'U' || znak == 'Y')
		return 1;
	else
		return 0;
}

// funkce k prikladu 24
int jeRostouci(int a, int b, int c) {
	if (a < b && b < c)
		return 1;
	else
		return 0;
}

// funkce k prikladu 25
int najdiMaximum(int a, int b, int c) {
	if (a > b && a > c)
		return a;
	else if (b > c)
		return b;
	else
		return c;
}

// funkce k prikladu 26
int vypocetFaktorialu(int cislo) {
	if (cislo < 0)
		return -1;
	else {
		int vysledek = 1;
		for (int i = 1; i <= cislo; i++)
			vysledek *= i;
		return vysledek;
	}
}

// funkce k prikladu 27
float vypocetPrumeru(float a, float b, float c) {
	float soucet = a + b + c;
	float vysledek = soucet / 3;
	return vysledek;
}

// funkce k prikladu 28
float penize(float vklad, float urok, int pocet_let) {
	for (int i = 0; i < pocet_let; i++) {
		vklad += (vklad / 100) * urok;
	}
	return vklad;
}

// funkce k prikladu 36
int vypocetSamohlasek(char slovo[]) {
	char samohlasky[] = {
		'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U', 'y', 'Y'};
	int pocet_samohlasek = 0;

	for (int i = 0; i < strlen(slovo); i++) {
		for (int j = 0; j < strlen(samohlasky); j++) {
			if (slovo[i] == samohlasky[j]) {
				pocet_samohlasek++;
			}
		}
	}
	return pocet_samohlasek;
}

// funkce k prikladu 43
int pythagorovaVeta(float a, float b, float c) {
	if ((c * c) == (a * a) + (b * b))
		return 1;
	else
		return 0;
}

// funkce k prikladu 44
float vypocetEur(float czk, float kurz) {
	return czk / kurz;
}

int main(void) {
	int vyber_prikladu = 0;
	do {
		printf("Zadej cislo prikladu ktery chces zobrazit (0 pro ukonceni): ");
		scanf("%d", &vyber_prikladu);

		switch (vyber_prikladu) {
		case 1:
			printf("-------------Priklad 1-------------\n");

			printf("Martin\nRybnikar\n");

			printf("\nVe zdrojovem kodu na radku: 115");
			break;
			//--------------------------------------------------------

		case 2:
			printf("-------------Priklad 2-------------\n");

			printf("Martin Rybnikar\n");
			printf("Rasovice 213\n");
			printf("685 01\n");

			printf("\nVe zdrojovem kodu na radcich: 124 - 126");
			break;
			//--------------------------------------------------------

		case 3:
			printf("-------------Priklad 3-------------\n");

			printf("Zadej postupne den, mesic a rok sveho narozeni:\n");
			int rok, mesic, den;
			scanf("%d %d %d", &den, &mesic, &rok);
			printf("Narodil si se %d. %d. %d\n", den, mesic, rok);

			printf("\nVe zdrojovem kodu na radcich: 135 - 138");
			break;
			//--------------------------------------------------------

		case 4:
			printf("-------------Priklad 4-------------\n");

			printf("Zadej dve cela cisla:\n");
			int a1, b1;
			scanf("%d %d", &a1, &b1);
			printf("Soucet cisel %d a %d je %d\n", a1, b1, a1 + b1);

			printf("\nVe zdrojovem kodu na radcich: 147 - 150");
			break;
			//--------------------------------------------------------

		case 5:
			printf("-------------Priklad 5-------------\n");

			printf("Zadej svuj vek:\n");
			int vek;
			scanf("%d", &vek);
			printf("Za %d let si prozil %d dni\n", vek, vek * 365);

			printf("\nVe zdrojovem kodu na radcich: 159 - 162");
			break;
			//--------------------------------------------------------

		case 6:
			printf("-------------Priklad 6-------------\n");

			printf("Zadej delku strany ctverce (jen cele cislo):\n");
			int delka_strany_ctverce;
			scanf("%d", &delka_strany_ctverce);

			printf("Obvod ctverce je: %d\n", 4 * delka_strany_ctverce);
			printf(
				"Obsah ctverce je: %d\n",
				delka_strany_ctverce * delka_strany_ctverce);

			printf("\nVe zdrojovem kodu na radcich: 171 - 176");
			break;
			//--------------------------------------------------------

		case 7:
			printf("-------------Priklad 7-------------\n");

			printf("Zadej velikost dvou vnitrnich uhlu trojuhelniku:\n");
			float alfa, beta;
			scanf("%f %f", &alfa, &beta);
			float gamma = 180 - alfa - beta;

			if (gamma <= 0)
				printf("Zadane uhly sou neplatne\n");
			else
				printf("Velikost tretiho uhlu je: %f", gamma);

			printf("\nVe zdrojovem kodu na radcich: 185 - 193");
			break;
			//--------------------------------------------------------

		case 8:
			printf("-------------Priklad 8-------------\n");

			printf("Zadej dve cela cisla pro porovnani:\n");
			int a8, b8;
			scanf("%d %d", &a8, &b8);

			if (a8 > b8)
				printf("Vetsi je prvni cislo\n");
			else if (a8 < b8)
				printf("Vetsi je druhe cislo\n");
			else
				printf("Cisla sou stejne\n");

			printf("\nVe zdrojovem kodu na radcich: 202 - 211");
			break;
			//--------------------------------------------------------

		case 9:
			printf("-------------Priklad 9-------------\n");

			printf("Zadej cele cislo:\n");
			int cislo9;
			scanf("%d", &cislo9);

			if (cislo9 > 0)
				printf("Zadane cislo je kladne\n");
			else if (cislo9 < 0)
				printf("Zadane cislo je zaporne\n");
			else
				printf("Zadane cislo je 0\n");

			printf("\nVe zdrojovem kodu na radcich: 220 - 229");
			break;
			//--------------------------------------------------------

		case 10:
			printf("-------------Priklad 10-------------\n");
			// kdyz sem pouzil float delalo to brikule v porovnavani - double je
			// cesta

			printf("Zadej rychlost v m/s:\n");
			double v1;
			scanf("%lf", &v1);
			printf("Zadej rychlost v km/h:\n");
			double v2;
			scanf("%lf", &v2);

			double v = v2 / 3.6;
			if (v > v1)
				printf("Vetsi je rychlost v km/h\n");
			else if (v < v1)
				printf("Vetsi je rychlost v m/s\n");
			else
				printf("Rychlosti sou stejne\n");

			printf("\nVe zdrojovem kodu na radcich: 239 - 251");
			break;
			//--------------------------------------------------------

		case 11:
			printf("-------------Priklad 11-------------\n");
			// nefungoval scanf bez mezery pred prvnim %c

			printf("Zadej postupne prvni znak ze jmena a prijmeni:\n");
			char inicial_jmena, inicial_prijmeni;
			scanf(" %c %c", &inicial_jmena, &inicial_prijmeni);
			printf("%c. %c.", inicial_jmena, inicial_prijmeni);

			printf("\nVe zdrojovem kodu na radcich: 261 - 264");
			break;
			//--------------------------------------------------------

		case 12:
			printf("-------------Priklad 12-------------\n");
			// scanf nefungoval bez mezery pred %c

			printf("Zadej znak:\n");
			char znak12;
			scanf(" %c", &znak12);

			if (znak12 == 'A')
				printf("Znak ktery si zadal je A\n");
			else
				printf("Znak ktery si zadal neni A\n");

			printf("\nVe zdrojovem kodu na radcich: 274 - 281");
			break;
			//--------------------------------------------------------

		case 13:
			printf("-------------Priklad 13-------------\n");

			printf("Zadel postupne dva znaky:\n");
			char prvni_znak13, druhy_znak13;
			scanf(" %c %c", &prvni_znak13, &druhy_znak13);

			if (prvni_znak13 == druhy_znak13)
				printf("Znaky ktere si zadal sou shodne\n");
			else
				printf("Znaky ktere si zadal sou rozdilne\n");

			printf("\nVe zdrojovem kodu na radcich: 290 - 297");
			break;
			//--------------------------------------------------------

		case 14:
			printf("-------------Priklad 14-------------\n");

			printf("Vypis cisel od 20 do 30:\n");
			for (int i = 20; i <= 30; i++)
				printf("%d\n", i);

			printf("\nVe zdrojovem kodu na radcich: 306 - 308");
			break;
			//--------------------------------------------------------

		case 15:
			printf("-------------Priklad 15-------------\n");

			printf("Vypis cisel od 0 do 100 po 10ti:\n");
			for (int i = 0; i <= 100; i = i + 10)
				printf("%d\n", i);

			printf("\nVe zdrojovem kodu na radcich: 317 - 319");
			break;
			//--------------------------------------------------------

		case 16:
			printf("-------------Priklad 16-------------\n");

			printf("Vypis cisel od 10 do 1\n");
			for (int i = 10; i > 0; i--)
				printf("%d\n", i);

			printf("\nVe zdrojovem kodu na radcich: 328 - 330");
			break;
			//--------------------------------------------------------

		case 17:
			printf("-------------Priklad 17-------------\n");

			printf("Vypis nasobku 3 od 30\n");
			for (int i = 30; i > 0; i = i - 3)
				printf("%d\n", i);

			printf("\nVe zdrojovem kodu na radcich: 339 - 341");
			break;
			//--------------------------------------------------------

		case 18:
			printf("-------------Priklad 18-------------\n");
			// mezera pred %c ve scnaf

			printf("Zadej znak:\n");
			char znak18;
			scanf(" %c", &znak18);

			for (int i = 0; i < 5; i++)
				printf("%c ", znak18);

			printf("\nVe zdrojovem kodu na radcich: 351 - 356");
			break;
			//--------------------------------------------------------

		case 19:
			printf("-------------Priklad 19-------------\n");

			int soucet19 = 0;
			for (int i = 1; i <= 10; i++)
				soucet19 += i;
			printf("Soucet vsech celych cisel od 1 do 10 je %d\n", soucet19);

			printf("\nVe zdrojovem kodu na radcich: 365 - 368");
			break;
			//--------------------------------------------------------

		case 20:
			printf("-------------Priklad 20-------------\n");

			printf("Zadej maximalni cislo, do ktereho se bude scitat:\n");
			int max20, soucet20 = 0;
			scanf("%d", &max20);

			for (int i = 1; i <= max20; i++)
				soucet20 += i;

			printf("Soucet cisel od 1 do %d je %d", max20, soucet20);

			printf("\nVe zdrojovem kodu na radcich: 377 - 384");
			break;
			//--------------------------------------------------------

		case 21:
			printf("-------------Priklad 21-------------\n");

			printf("Zadej dve cisla pro porovnani:\n");
			int a21, b21;
			scanf("%d %d", &a21, &b21);
			int vysledek21 = porovnaniCisel(a21, b21);

			if (vysledek21 == 1)
				printf("Prvni cislo je vetsi\n");
			else if (vysledek21 == 0)
				printf("Cisla jsou stejna\n");
			else
				printf("Druhe cislo je vetsi\n");

			printf("\nVe zdrojovem kodu na radcich: 393 - 403, pouzita funkce: "
				   "5 - 12");
			break;
			//--------------------------------------------------------

		case 22:
			printf("-------------Priklad 22-------------\n");

			printf("Zadej cislo:\n");
			int cislo22;
			scanf("%d", &cislo22);
			int vysledek22 = jeZaporne(cislo22);

			if (vysledek22 == 1)
				printf("Cislo je kladne\n");
			else if (vysledek22 == 0)
				printf("Cislo je 0\n");
			else
				printf("Cislo je zaporne\n");

			printf("\nVe zdrojovem kodu na radcich: 412 - 422, pouzita funkce: "
				   "15 - 22");
			break;
			//--------------------------------------------------------

		case 23:
			printf("-------------Priklad 23-------------\n");

			printf("Zadej znak pro porovnani:\n");
			char znak23;
			scanf(" %c", &znak23);
			int vysledek23 = jeVelkaSamohlaska(znak23);

			if (vysledek23 == 1)
				printf("Zadany znak je velka samohlaska\n");
			else
				printf("Zadany znak neni velka samohlaska\n");

			printf("\nVe zdrojovem kodu na radcich: 431 - 439, pouzita funkce: "
				   "25 - 30");
			break;
			//--------------------------------------------------------

		case 24:
			printf("-------------Priklad 24-------------\n");

			printf("Zadej postupne tri cela cisla:\n");
			int a24, b24, c24;
			scanf("%d %d %d", &a24, &b24, &c24);
			int vysledek24 = jeRostouci(a24, b24, c24);

			if (vysledek24 == 1)
				printf("Cisla tvori postupne rostouci radu\n");
			else
				printf("Cisla netvori postupne rostouci radu\n");

			printf("\nVe zdrojovem kodu na radcich: 448 - 456, pouzita funkce: "
				   "33 - 38");
			break;
			//--------------------------------------------------------

		case 25:
			printf("-------------Priklad 25-------------\n");

			printf("Zadej tri cela cislo pro urceni nejvetsiho z nich\n");
			int a25, b25, c25;
			scanf("%d %d %d", &a25, &b25, &c25);
			int vysledek25 = najdiMaximum(a25, b25, c25);
			printf("Nejvetsi cislo je %d\n", vysledek25);

			printf("\nVe zdrojovem kodu na radcich: 465 - 469, pouzita funkce: "
				   "41 - 48");
			break;
			//--------------------------------------------------------

		case 26:
			printf("-------------Priklad 26-------------\n");

			printf("Zadej cislo ze ktereho chces vypocitat faktorial:\n");
			int cislo26;
			scanf("%d", &cislo26);
			int vysledek26 = vypocetFaktorialu(cislo26);

			if (vysledek26 == -1)
				printf("Faktorial ze zaporneho cisla neni definovany\n");
			else
				printf("Faktorial z cisla %d je %d\n", cislo26, vysledek26);

			printf("\nVe zdrojovem kodu na radcich: 478 - 486, pouzita funkce: "
				   "51 - 60");
			break;
			//--------------------------------------------------------

		case 27:
			printf("-------------Priklad 27-------------\n");

			printf("Zadej tri cisla pro vypocitani prumeru:\n");
			float a27, b27, c27;
			scanf("%f %f %f", &a27, &b27, &c27);
			float vysledek27 = vypocetPrumeru(a27, b27, c27);
			printf("Prumer z cisel %f %f %f je %f", a27, b27, c27, vysledek27);

			printf("\nVe zdrojovem kodu na radcich: 495 - 499, pouzita funkce: "
				   "63 - 68");
			break;
			//--------------------------------------------------------

		case 28:
			printf("-------------Priklad 28-------------\n");
			// diky %.2f se vypise cislo s pouze 2 desitinima mistama

			float vklad, urok;
			printf("Zadej pocatecni vklad:\n");
			scanf("%f", &vklad);

			printf("Zadej rocni urokovou sazbu (v procentech):\n");
			scanf("%f", &urok);

			int pocet_let;
			printf("Zadej dobu urokove sazby:\n");
			scanf("%d", &pocet_let);

			float vysledek28 = penize(vklad, urok, pocet_let);
			printf(
				"Zustatek za %d let pri urokove sazbe %.2f procent z "
				"pocatecniho vkladu %.2f je %.2f\n",
				pocet_let,
				urok,
				vklad,
				vysledek28);

			printf("\nVe zdrojovem kodu na radcich: 509 - 521, pouzita funkce: "
				   "70 - 75");
			break;
			//--------------------------------------------------------

		case 29:
			printf("-------------Priklad 29-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char slovo29[21];
			scanf("%s", slovo29);

			for (int i = 0; i < strlen(slovo29); i++)
				printf("%c\n", slovo29[i]);

			printf("\nVe zdrojovem kodu na radcich: 530 - 535");
			break;
			//--------------------------------------------------------

		case 30:
			printf("-------------Priklad 30-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char slovo30[21];
			scanf("%s", slovo30);

			for (int i = strlen(slovo30) - 1; i >= 0; i--)
				printf("%c\n", slovo30[i]);

			printf("\nVe zdrojovem kodu na radcich: 544 - 549");
			break;
			//--------------------------------------------------------

		case 31:
			printf("-------------Priklad 31-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char slovo31[21];
			scanf("%s", slovo31);
			int pocet_a = 0;

			for (int i = 0; i < strlen(slovo31); i++) {
				if (slovo31[i] == 'a')
					pocet_a++;
			}
			printf("Ve slove %s se 'a' nachazi %d\n", slovo31, pocet_a);

			printf("\nVe zdrojovem kodu na radcich: 558 - 567");
			break;
			//--------------------------------------------------------

		case 32:
			printf("-------------Priklad 32-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char slovo32[21];
			scanf("%s", slovo32);
			int pocet_Aa = 0;

			for (int i = 0; i < strlen(slovo32); i++) {
				if (slovo32[i] == 'a' || slovo32[i] == 'A')
					pocet_Aa++;
			}
			printf("Ve slove %s se 'a' a 'A' nachazi %d\n", slovo32, pocet_Aa);

			printf("\nVe zdrojovem kodu na radcich: 576 - 585");
			break;
			//--------------------------------------------------------

		case 33:
			printf("-------------Priklad 33-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char slovo33[21];
			scanf("%s", slovo33);

			for (int i = strlen(slovo33) - 2; i < strlen(slovo33); i++)
				printf("%c", slovo33[i]);

			printf("\n"); // <-- aby to lip vypadalo na funkcnost to nema vliv

			printf("\nVe zdrojovem kodu na radcich: 594 - 599");
			break;
			//--------------------------------------------------------

		case 34:
			printf("-------------Priklad 34-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char prvni_slovo34[21], druhy_slovo34[21];
			scanf("%s", prvni_slovo34);
			int pomoc34 = strlen(prvni_slovo34) - 1;

			for (int i = 0; i < strlen(prvni_slovo34); i++) {
				druhy_slovo34[pomoc34] = prvni_slovo34[i];
				pomoc34--;
			}

			for (int i = 0; i < strlen(prvni_slovo34); i++) {
				printf("%c  %c\n", prvni_slovo34[i], druhy_slovo34[i]);
			}

			printf("\nVe zdrojovem kodu na radcich: 310 - 622");
			break;
			//--------------------------------------------------------

		case 35:
			printf("-------------Priklad 35-------------\n");

			printf("Zadej libovolne dve slova, kazde kratsi nez 20 znaku:\n");
			char prvni_slovo35[21], druhy_slovo35[21];
			scanf("%s %s", prvni_slovo35, druhy_slovo35);

			int delka_prvni_slovo35 = strlen(prvni_slovo35);
			int delka_druhy_slovo35 = strlen(druhy_slovo35);

			if (delka_prvni_slovo35 > delka_druhy_slovo35)
				printf("Prvni slovo je delsi\n");
			else if (delka_prvni_slovo35 < delka_druhy_slovo35)
				printf("Druhy slovo je delsi\n");
			else
				printf("Obe slova sou stejne dlouha\n");

			printf("\nVe zdrojovem kodu na radcich: 631 - 643");
			break;
			//--------------------------------------------------------

		case 36:
			printf("-------------Priklad 36-------------\n");

			printf("Zadej libovolne slovo kratsi nez 20 znaku:\n");
			char slovo36[21];
			scanf("%s", slovo36);
			int vysledek36 = vypocetSamohlasek(slovo36);
			printf("Slovo %s ma %d samohlasek\n", slovo36, vysledek36);

			printf("\nVe zdrojovem kodu na radcich: 652 - 656, pouzita funkce: "
				   "78 - 90");
			break;
			//--------------------------------------------------------

		case 37:
			printf("-------------Priklad 37-------------\n");

			printf("Zadej postupne pet celych cisel pro najiti nejvetsiho z "
				   "nich:\n");
			int cisla37[5];
			for (int i = 0; i < 5; i++)
				scanf("%d", &cisla37[i]);

			int max37 = cisla37[0];
			for (int i = 0; i < 5; i++) {
				if (max37 < cisla37[i])
					max37 = cisla37[i];
			}
			printf("Nejvetsi cislo je %d\n", max37);

			printf("\nVe zdrojovem kodu na radcich: 665 - 675");
			break;
			//--------------------------------------------------------

		case 38:
			printf("-------------Priklad 38-------------\n");

			printf("Zadej postupne pet celych cisel:\n");
			int cisla38[5];
			for (int i = 0; i < 5; i++)
				scanf("%d", &cisla38[i]);

			int soucet38 = 0;
			for (int i = 0; i < 5; i++)
				soucet38 += cisla38[i];
			printf("Soucet vsech cisel je %d\n", soucet38);

			printf("\nVe zdrojovem kodu na radcich: 684 - 692");
			break;
			//--------------------------------------------------------

		case 39:
			printf("-------------Priklad 39-------------\n");

			printf("Zadej postupne 7 cisel:\n");
			float cisla39[7];
			for (int i = 0; i < 7; i++) {
				scanf("%f", &cisla39[i]);
			}

			// serazeni pole
			for (int i = 0; i < 7; i++) {
				for (int j = i; j < 7; j++) {
					if (cisla39[j] < cisla39[i]) {
						float pomoc = cisla39[j];
						cisla39[j] = cisla39[i];
						cisla39[i] = pomoc;
					}
				}
			}

			printf("Serazene pole:\n");
			for (int i = 0; i < 7; i++)
				printf("%f\n", cisla39[i]);

			printf("\nVe zdrojovem kodu na radcich: 701 - 720");
			break;
			//--------------------------------------------------------

		case 40:
			printf("-------------Priklad 40-------------\n");

			printf("Zadej 7 cisel pro najiti nejmensiho:\n");
			float cisla40[7];
			for (int i = 0; i < 7; i++)
				scanf("%f", &cisla40[i]);

			float min40 = cisla40[0];
			for (int i = 0; i < 7; i++) {
				if (min40 > cisla40[i])
					min40 = cisla40[i];
			}

			printf("Nejmensi cislo je %f\n", min40);

			printf("\nVe zdrojovem kodu na radcich: 729 - 740");
			break;
			//--------------------------------------------------------

		case 41:
			printf("-------------Priklad 41-------------\n");

			printf("Zadej 7 cisel pro vypocitani prumeru:\n");
			float cisla41[7], soucet41 = 0;
			for (int i = 0; i < 7; i++) {
				scanf("%f", &cisla41[i]);
				soucet41 += cisla41[i];
			}
			float prumer41 = soucet41 / 7;
			printf("Prumer z techto cisel je %f\n", prumer41);

			printf("\nVe zdrojovem kodu na radcich: 749 - 756");
			break;
			//--------------------------------------------------------

		case 42:
			printf("-------------Priklad 42-------------\n");

			printf("Zadej postupne 5 celych cisel:\n");
			int cisla42[5], soucet42 = 0;
			for (int i = 0; i < 5; i++) {
				scanf("%d", &cisla42[i]);
				soucet42 += cisla42[i];
			}

			float prumer42 = soucet42 / 5;
			int pocet_cisel_mensich = 0;
			for (int i = 0; i < 5; i++) {
				if (cisla42[i] < prumer42)
					pocet_cisel_mensich++;
			}
			printf(
				"Prumer z techto cisel je %f a pocet cisel mensich nez prumer "
				"je %d\n",
				prumer42,
				pocet_cisel_mensich);

			printf("\nVe zdrojovem kodu na radcich: 765 - 778");
			break;
			//--------------------------------------------------------

		case 43:
			printf("-------------Priklad 43-------------\n");

			printf("Zadej postupne delky vsech 3 stran trojuhelniku:\n");
			float a43, b43, c43;
			scanf("%f %f %f", &a43, &b43, &c43);
			int vysledek43 = pythagorovaVeta(a43, b43, c43);

			if (vysledek43 == 1)
				printf("Trojuhelnik je pravouhly\n");
			else
				printf("Trojuhelnik neni pravouhly\n");

			printf("\nVe zdrojovem kodu na radcich: 787 - 795, pouzita funkce: "
				   "93 - 98");
			break;
			//--------------------------------------------------------

		case 44:
			printf("-------------Priklad 44-------------\n");

			printf("Zadej cenu v czk:\n");
			float czk;
			scanf("%f", &czk);

			printf("Zadej kurz z czk na euro:\n");
			float kurz;
			scanf("%f", &kurz);

			float vysledek44 = vypocetEur(czk, kurz);
			printf("%f czk je pri kurzu %f %f euro\n", czk, kurz, vysledek44);

			printf("\nVe zdrojovem kodu na radcich: 804 - 813, pouzita funkce: "
				   "101 - 103");
			break;
			//--------------------------------------------------------

		case 0:
			break;

		default:
			printf("Zadal si neplatnou hondotu, zkus to znovu\n");
			break;
		}

		if (vyber_prikladu != 0)
			printf("\n------------------------------------------\n\n");

	} while (vyber_prikladu != 0);

	printf("konec");
	return 0;
}