#include "Vypis_areny.h"

void Vypis_areny::uvitani() {
    cout << BOLDWHITE << "--------------------" << endl;
    cout << "Vitej v arene." << endl;
    cout << "--------------------" << RESET << endl << endl;
}

void Vypis_areny::zalozeni(Hrac hrac1, Hrac hrac2) {
    for (int i = 0; i < vyska; i++) {
        for (int j = 0; j < sirka; j++) {
            this->arena[i][j] = ' ';
        }
    }

    for (int i = 0; i < sirka; i++) {
        this->arena[0][i] = '-';
    }

    for (int i = 1; i < vyska - 1; i++) {
        arena[i][0] = '|';
        arena[i][sirka - 1] = '|';
    }

    for (int i = 0; i < sirka; i++) {
        arena[vyska - 1][i] = '-';
    }

    arena[3][zakladni_pozice1] = hrac1.znak[0];
    pozice1 = zakladni_pozice1;
    arena[3][zakladni_pozice2] = hrac2.znak[0];
    pozice2 = zakladni_pozice2;

    vypis();
}

void Vypis_areny::vypis() {
    cout << BOLDWHITE << "Arena vypada takto: " << endl;
    for (int i = 0; i < vyska; i++) {
        for (int j = 0; j < sirka; j++) {
            if (arena[i][j] == hrac1.znak[0] || arena[i][j] == hrac2.znak[0]) {
                cout << BOLDCYAN << arena[i][j] << RESET;
            }
            else
                cout << this->arena[i][j];
        }
        cout << RESET << endl;
    }
    /*cout << BOLDGREEN << hrac1.jmeno << ": " << BOLDWHITE << hrac1.bojovnik.hp << "hp" << endl;
    cout << BOLDGREEN << hrac2.jmeno << ": " << BOLDWHITE << hrac2.bojovnik.hp << "hp" << RESET << endl;*/

};

void Vypis_areny::pohyb(Hrac hrac) {
    char smer;
here:
    cin >> smer;
sem:    
    if (hrac.poradi == 1) {
        if (smer == 'P' || smer == 'p') {
            if (arena[3][pozice1 + hrac.bojovnik.pocet_policek] == ' ') {
                arena[3][pozice1] = ' ';
                pozice1 += hrac.bojovnik.pocet_policek;
                arena[3][pozice1] = hrac.znak[0];
            }
            else {
                cout << "Nelze jit na tuto stranu" << endl;
                smer = 'l';
                goto sem;
            }
        }
        else if (smer == 'L' || smer == 'l') {
            if (arena[3][pozice1 - hrac.bojovnik.pocet_policek] == ' ') {
                arena[3][pozice1] = ' ';
                pozice1 -= hrac.bojovnik.pocet_policek;
                arena[3][pozice1] = hrac.znak[0];
            }
            else {
                cout << "Nelze jit na tuto stranu" << endl;
                smer = 'p';
                goto sem;
            }
        }
        else{
          cout << "Neplatna hodnota" << endl << "Zadej platnou stranu" << endl;
          goto here;
        }
    }
    else if(hrac.poradi == 2){
        if (smer == 'P' || smer == 'p') {
            if (arena[3][pozice2 + hrac.bojovnik.pocet_policek] == ' ') {
                arena[3][pozice2] = ' ';
                pozice2 += hrac.bojovnik.pocet_policek;
                arena[3][pozice2] = hrac.znak[0];
            }
            else {
                cout << "Nelze jit na tuto stranu" << endl;
                smer = 'l';
                goto sem;
            }
        }
        else if (smer == 'L' || smer == 'l') {
            if (arena[3][pozice2 - hrac.bojovnik.pocet_policek] == ' ') {
                arena[3][pozice2] = ' ';
                pozice2 -= hrac.bojovnik.pocet_policek;
                arena[3][pozice2] = hrac.znak[0];
            }
            else {
                cout << "Nelze jit na tuto stranu" << endl;
                smer = 'p';
                goto sem;
            }
        }
    }
    else{
          cout << "Neplatna hodnota" << endl << "Zadej platnou stranu" << endl;
          goto here;
      }
}

void Vypis_areny::vyberAkce(Hrac hrac1, Hrac hrac2) {
    while (hrac1.bojovnik.hp > 0 && hrac2.bojovnik.hp > 0) {
    here:
        cout << BOLDWHITE << "Hraci " << BOLDGREEN << hrac1.jmeno << BOLDWHITE << " vyber si z nasledujicich moznosti:" << endl;
        cout << "1.Pohyb" << endl;
        cout << "2.Utok (musis byt v blizkosti nepritele)" << endl;
        cout << "3.Pauza (obnovi zivoty podle bojovnika)" << RESET << endl;

        cin >> vyber_akce;

        if (vyber_akce == "1" || vyber_akce == "Pohyb" || vyber_akce == "pohyb") {
            cout << BOLDWHITE << "Na jakou stranu chces jit? (L / P)" << RESET << endl;

            pohyb(hrac1);
        }
        else if (vyber_akce == "2" || vyber_akce == "Utok" || vyber_akce == "utok") {
            if (arena[3][pozice1 - hrac1.bojovnik.vzdalenost] == hrac2.znak[0] || arena[3][pozice1 + hrac1.bojovnik.vzdalenost] == hrac2.znak[0]) {
                hrac2.utokNaHrace2(hrac1, hrac2);
            }
            else {
                cout << BOLDWHITE << "Souper neni v tvem dosahu" << RESET << endl << endl;
                goto here;
            }
        }
        else if (vyber_akce == "3" || vyber_akce == "Pauza" || vyber_akce == "pauza") {
            hrac1.pauza();
        }
        else {
            cout << BOLDWHITE << "Neplatna hodnota" << RESET << endl << endl;
            goto here;
        }
        cout << endl << BOLDYELLOW << "---------------------------------------" << RESET << endl << endl;
        vypis();
        cout << BOLDGREEN << hrac1.jmeno << ": " << BOLDWHITE << hrac1.bojovnik.hp << "hp" << endl;
        cout << BOLDGREEN << hrac2.jmeno << ": " << BOLDWHITE << hrac2.bojovnik.hp << "hp" << RESET << endl;

        

        if (hrac1.bojovnik.hp > 0 && hrac2.bojovnik.hp > 0) {
        sem:
            cout << BOLDWHITE << "Hraci " << BOLDGREEN << hrac2.jmeno << BOLDWHITE << " vyber si z nasledujicich moznosti:" << endl;
            cout << "1.Pohyb" << endl;
            cout << "2.Utok (musis byt v blizkosti nepritele)" << endl;
            cout << "3.Pauza (obnovi zivoty podle bojovnika)" << RESET << endl;

            cin >> vyber_akce;

            if (vyber_akce == "1" || vyber_akce == "Pohyb" || vyber_akce == "pohyb") {
                cout << BOLDWHITE << "Na jakou stranu chces jit? (L / P)" << RESET << endl;

                pohyb(hrac2);
            }
            else if (vyber_akce == "2" || vyber_akce == "Utok" || vyber_akce == "utok") {
                if (arena[3][pozice2 - hrac2.bojovnik.vzdalenost] == hrac1.znak[0] || arena[3][pozice2 + hrac2.bojovnik.vzdalenost] == hrac1.znak[0]) {
                    hrac1.utokNaHrace1(hrac1, hrac2);
                }
                else {
                    cout << BOLDWHITE << "Souper neni v tvem dosahu" << RESET << endl << endl;
                    goto sem;
                }
            }
            else if (vyber_akce == "3" || vyber_akce == "Pauza" || vyber_akce == "pauza") {
                hrac2.pauza();
            }
            else {
                cout << BOLDWHITE << "Neplatna hodnota" << RESET << endl << endl;
                goto sem;
            }
            cout << endl << BOLDYELLOW << "---------------------------------------" << RESET << endl << endl;
            vypis();
            cout << BOLDGREEN << hrac1.jmeno << ": " << BOLDWHITE << hrac1.bojovnik.hp << "hp" << endl;
            cout << BOLDGREEN << hrac2.jmeno << ": " << BOLDWHITE << hrac2.bojovnik.hp << "hp" << RESET << endl;

            
        }
    }

    if (hrac1.bojovnik.hp == hrac2.bojovnik.hp) {
        cout << BOLDGREEN << "plichta s hp " << hrac1.bojovnik.hp << RESET << endl;
    }
    else if (hrac1.bojovnik.hp > hrac2.bojovnik.hp) {
        cout << BOLDGREEN << "hrac " << hrac1.jmeno << " vyhral s hp " << hrac1.bojovnik.hp << RESET << endl;
    }
    else {
        cout << BOLDGREEN << "hrac " << hrac2.jmeno << " vyhral s hp " << hrac2.bojovnik.hp << RESET << endl;
    }
}