#include <stdio.h>

//------------------------------------ Struktury ------------------------------------
typedef struct JmenoKontaktu{
    char arr[101];
    int delka;
} JmenoKontaktu;

typedef struct TelefoniCislo{
    char arr[101];
    int delka;
} TelefoniCislo;

typedef struct Kontakt{
    JmenoKontaktu jmeno;
    TelefoniCislo cislo;
} Kontakt;

typedef struct Cislice{
    char znaky[5];
    int pocet_znaku;
} Cislice;

//------------------------------------- Funkce -------------------------------------
/**
 * @param argv[1]
 *
 * @return 0 první znak není číslice
 * @return 1 první znak je číslice
 */
int kontrolaArgv(char argv[]){
    if(argv[0] >= '0' && argv[0] <= '9')
        return 1;

    return 0;
}

/**
 * @param argc
 *
 * @return 0 - argc > 2 (moc argumentů)
 * @return 1 - argc == 1 (výpis celého seznamu)
 * @return 2 - argc == 2 (výpis podle kritéria)
 */
int kontrolaArgc(int argc){
    if(argc == 1)
        return 1;
    if(argc > 2)
        return 0;

    return 2;
}

/**
 * Funkce, která na všechny pozice v poli charu dosadí hodnotu 0
 *
 * @param pole
 * @param delka
 */
void vynulovaniPole(char pole[], int delka){
    for(int i = 0; i < delka; i++)
        pole[i] = 0;
}

/**
 *
 * @param kontakty
 *
 * @return leckový počet kontaktů v seznamu
 */
int naplneniKontaktu(Kontakt kontakty[]){
    for(int i = 0; i < 42; i++) {
        vynulovaniPole(kontakty[i].jmeno.arr, 101);
        kontakty[i].jmeno.delka = 0;
        vynulovaniPole(kontakty[i].cislo.arr, 101);
        kontakty[i].cislo.delka = 0;
    }

    int _znak;
    int znak;
    int aktualni_radek = 0;
    int celkovy_pocet_radku = 0;
    int help = 0;
    while(1) {
        znak = getchar();

        if (znak == EOF)
            break;

        if(znak == '!') {
            if (_znak == '\n')
                celkovy_pocet_radku--;
            break;
        }

        if(celkovy_pocet_radku > 41) {
            celkovy_pocet_radku--;
            break;
        }

        if (znak == '\n') {
            if (help % 2 == 0)
                help++;
            else {
                celkovy_pocet_radku++;
                help = 0;
            }
            aktualni_radek = 0;
            _znak = znak;
            continue;
        }

        if(help % 2 == 1){
            if(!((znak >= '0' && znak <= '9') || znak == '+'))
                return -1;
        }

        if(aktualni_radek < 101) {
            if (help % 2 == 0) {
                kontakty[celkovy_pocet_radku].jmeno.arr[aktualni_radek] = znak;
                kontakty[celkovy_pocet_radku].jmeno.delka++;
            }
            else {
                kontakty[celkovy_pocet_radku].cislo.arr[aktualni_radek] = znak;
                kontakty[celkovy_pocet_radku].cislo.delka++;
            }
        }

        if (znak != '\n') {
            aktualni_radek++;
        }
        _znak = znak;
    }
    return celkovy_pocet_radku + 1;
}

/**
 * Vypisuje do konzole celkový seznam kontaktů
 *
 * @param kontakty
 * @param pocet
 */
void vypisVsechKontaktu(Kontakt kontakty[], int pocet){
    for(int i = 0; i < pocet; i++){
        printf("%s, %s\n", kontakty[i].jmeno.arr, kontakty[i].cislo.arr);
    }
}

/**
 * Vypisuje do konzole jeden konkrétní kontakt
 *
 * @param kontakt
 */
void vypisJednohoKontaktu(Kontakt kontakt){
    printf("%s, %s\n", kontakt.jmeno.arr, kontakt.cislo.arr);
}

/**
 * Funkce, která naplné pole čísel konkrétníma hodnotama, pro pozdější určení kritéria
 *
 * @param cisla - pole čísel do kterého uloží hodnoty
 */
void zalozeniCislic(Cislice cislice[]){
    cislice[0].pocet_znaku = 2;
    cislice[1].pocet_znaku = 1;
    cislice[2].pocet_znaku = 4;
    cislice[3].pocet_znaku = 4;
    cislice[4].pocet_znaku = 4;
    cislice[5].pocet_znaku = 4;
    cislice[6].pocet_znaku = 4;
    cislice[7].pocet_znaku = 5;
    cislice[8].pocet_znaku = 4;
    cislice[9].pocet_znaku = 5;

    for(int i = 0; i < 10; i++)
        vynulovaniPole(cislice[i].znaky, cislice[i].pocet_znaku);

    for(int i = 0; i < 10; i++){
        cislice[i].znaky[0] = '0' + i;
    }

    cislice[0].znaky[1] = '+';

    int j = 1;
    int z = 2;
    for(int i = 0; i < 26; i++){
        if(j == cislice[z].pocet_znaku){
            j = 1;
            z++;
        }
        cislice[z].znaky[j++] = 'a' + i;
    }
}

/**
 * Funkce pro získání číslice, která je v požadované pozici kritéria zadaného uživatelem
 *
 * @param cisla
 * @param kriterium
 *
 * @return požadovaný index v poli
 */
int getCislici(Cislice cislice[], char kriterium){
    for (int j = 0; j < 10; j++) {
        if (kriterium == cislice[j].znaky[0])
            return j;
    }
}

/**
 * Funkce která vrací kolikrát se vyskytují znaky, které reprezentuje první zadaná číslice v kritériu, ve jméně kontaktu
 *
 * @param jmeno
 * @param znaky
 * @param delka
 *
 * @return Počet kolikrát se vyskytují znaky ve slově
 */
int getPocetOpakovaniJmeno(JmenoKontaktu jmeno, Cislice cislice){
    int res = 0;
    for (int z = 0; z < jmeno.delka; z++) {
        for (int u = 0; u < cislice.pocet_znaku; u++) {
            if (jmeno.arr[z] == cislice.znaky[u] || jmeno.arr[z] == cislice.znaky[u] - 32)
                res++;
        }
    }

    return res;
}

/**
 * Vrací počet prvků v kriteriu
 *
 * @param kriterium
 * @return
 */
int getPocetPrvkuKriteria(char kriterium[]){
    int res = 0;
    //spočítá celkovou délku zadaného kritéria
    while(kriterium[res] >= '0' && kriterium[res] <= '9'){
        res++;
    }
    return res;
}

/**
 * Vrací kolikrát se vyskytuje vyskytuje první znak kritéria v telefoním čísle
 *
 * @param cislo
 * @param kriterium
 * @return
 */
int getPocetOpakovaniCislo(TelefoniCislo cislo, char kriterium){
    //Určení kolikrát se znaky kritéria vyskytují v čísle kontaktu
    int res = 0;
    for (int z = 0; z < cislo.delka; z++){
        if(kriterium == '0'){
            if (cislo.arr[z] == '0' || cislo.arr[z] == '+')
                res++;
        }
        else {
            if (cislo.arr[z] == kriterium)
                res++;
        }
    }
    return res;
}

/**
 * Funkce která zkontroluje zda se v některým z kontaktů kriteriům nevyskytuje s přerušenou posloupností, pokud ano
 * tyto kontakty vypíše, zavolá se pouze pokud funkce na vypis přímé posloupnosti nenalezne žádný kontakt
 *
 * @param kontakty
 * @param kriterium
 * @param cislice
 * @param celkem_kontaktu
 */
void vypisNeprimePosloupnosti(Kontakt kontakty[], char kriterium[], Cislice cislice[], int celkem_kontaktu){
    int prvku_kriteria = getPocetPrvkuKriteria(kriterium);

    int pocet_nalezenych = 0;
    int souradnice_nalezenych[42];

    for(int i = 0; i < celkem_kontaktu; i++){
        int k = 0;  //Index pro průchod polem kritéria
        int j;  //Index pro průchod polem čísel
        int validace = 0;
        int splneno = 0;

        j = getCislici(cislice, kriterium[k]);
        int kolik_opakovani = getPocetOpakovaniJmeno(kontakty[i].jmeno, cislice[j]);
        //Cyklus, který proběhne tolikrát kolikrát se vyskytuje první prvek kritéria ve jméně
        for(int a = 0; a < kolik_opakovani; a++){
            int pruchod;
            splneno = 0;
            validace = 0;

            //Cyklus hledá na jaké pozici se kritérium vyskytuje a tuto pozici uloží
            for(int z = 0; z < kontakty[i].jmeno.delka; z++){
                for(int b = 0; b < cislice[j].pocet_znaku; b++){
                    if(kontakty[i].jmeno.arr[z] == cislice[j].znaky[b] || kontakty[i].jmeno.arr[z] == cislice[j].znaky[b] - 32){
                        pruchod = z;
                        splneno = 1;
                        validace++;
                        break;
                    }
                }
                if(splneno)
                    break;
            }
            if(splneno) {
                k++;
                //Cyklus který se opakuje dokud je kritérium v požadovaným tvaru a kontroluje zda se vyskytuje ve jméně za
                //dříve získanou pozicí
                while (kriterium[k] >= '0' && kriterium[k] <= '9'){
                    j = getCislici(cislice, kriterium[k]);
                    splneno = 0;
                    for(int z = pruchod + 1; z < kontakty[i].jmeno.delka; z++){
                        for(int b = 0; b < cislice[j].pocet_znaku; b++){
                            if(kontakty[i].jmeno.arr[z] == cislice[j].znaky[b] || kontakty[i].jmeno.arr[z] == cislice[j].znaky[b] - 32){
                                pruchod = z;
                                splneno = 1;
                                validace++;
                                break;
                            }
                        }
                        if(splneno)
                            break;
                    }
                    if(!splneno)
                        break;
                    k++;
                }

                if(splneno && validace == prvku_kriteria){
                    souradnice_nalezenych[pocet_nalezenych++] = i;
                    break;
                }
            }
        }
        //Pokud jméno kontaktu nevyhovalo zkusí se jeho číslo, funguje téměř stejně jen porovnává číslo místo jména
        if(!splneno){
            kolik_opakovani = getPocetOpakovaniCislo(kontakty[i].cislo, kriterium[0]);

            for(int a = 0; a < kolik_opakovani; a++) {
                int pruchod = 0;
                validace = 0;
                splneno = 0;
                k = 0;

                //Najití pozice požadovaného znaku
                for (int z = pruchod; z < kontakty[i].cislo.delka; z++) {
                    if(kriterium[k] == '0'){
                        if (kontakty[i].cislo.arr[z] == '0' || kontakty[i].cislo.arr[z] == '+') {
                            pruchod = z;
                            splneno = 1;
                            validace++;
                            break;
                        }
                    }
                    else {
                        if (kontakty[i].cislo.arr[z] == kriterium[k]) {
                            pruchod = z;
                            splneno = 1;
                            validace++;
                            break;
                        }
                    }
                }
                //Kontrola zda i navazující znaky vyhovují kritériu
                if (splneno) {
                    k++;
                    while (kriterium[k] >= '0' && kriterium[k] <= '9') {
                        splneno = 0;
                        if(kriterium[k] == '0'){
                            for(int z = pruchod + 1; z < kontakty[i].cislo.delka; z++) {
                                if (kontakty[i].cislo.arr[z] == '0' || kontakty[i].cislo.arr[z] == '+') {
                                    pruchod = z;
                                    splneno = 1;
                                    validace++;
                                    break;
                                }
                            }
                        }
                        else {
                            for(int z = pruchod + 1; z < kontakty[i].cislo.delka; z++) {
                                if (kontakty[i].cislo.arr[z] == kriterium[k]) {
                                    pruchod = z;
                                    splneno = 1;
                                    validace++;
                                    break;
                                }
                            }
                        }
                        if(!splneno)
                            break;
                        k++;
                    }
                    //Pokud vše vyhovuje přidá se kontakt do seznamu k vypsání
                    if (splneno && validace == prvku_kriteria) {
                        souradnice_nalezenych[pocet_nalezenych++] = i;
                        break;
                    }
                }
            }
        }
    }
    if(pocet_nalezenych > 0) {
        fprintf(stderr, "Nenalezeny zadne pozadovane kontakty s neprerusenou posloupnosti\n\n");
        printf("Kontakty s prerusenou posloupnosti:\n");
        for (int i = 0; i < pocet_nalezenych; i++) {
            vypisJednohoKontaktu(kontakty[souradnice_nalezenych[i]]);
        }
    }
    else
        fprintf(stderr, "Nenalezeny zadno pozadovane kontakty, ani s prerusenou posloupnosti\n");
}

/**
 * Funkce, která vypíše konkrétní kontakty podle zadaného kritéria, rozhoduje o tom který záznam vypíše a který ne
 *
 * @param kontakty
 * @param kriterium
 * @param cisla
 * @param celkem_kontaktu
 */
void vypisPrimePosloupnosti(Kontakt kontakty[], char kriterium[], Cislice cislice[], int celkem_kontaktu){
    int prvku_kriteria = getPocetPrvkuKriteria(kriterium);

    int pocet_nalezenych = 0;
    int souradnice_nalezenych[42];
    //Cyklus, který projde postupně všechny kontakty
    for(int i = 0; i < celkem_kontaktu; i++){
        int k = 0;  //Index pro průchod polem kritéria
        int j;  //Index pro průchod polem čísel

        int splneno = 0;
        int pruchod = 0;
        int kolik_opakovani;
        int validace = 0;

        j = getCislici(cislice, kriterium[k]);

        kolik_opakovani = getPocetOpakovaniJmeno(kontakty[i].jmeno, cislice[j]);

        //Cyklus, který postupně projde všechny první prvky kritéria ve jméně kontaktu (když jméno obsahuje např. víckrát
        //'a', cyklus proběhne tolikrát kolik 'a' ve jméně je a postupně je zontroluje dokud nebude některé vyhovovat
        for (int a = 0; a < kolik_opakovani; a++) {
            validace = 0;
            splneno = 0;
            k = 0;

            j = getCislici(cislice, kriterium[k]);

            //Cyklus sloužící pro najití pozice požadovaného znaku
            for (int z = pruchod; z < kontakty[i].jmeno.delka; z++) {
                if(kontakty[i].jmeno.arr[z] != ' ') {
                    for (int b = 0; b < cislice[j].pocet_znaku; b++) {
                        if (kontakty[i].jmeno.arr[z] == cislice[j].znaky[b] || kontakty[i].jmeno.arr[z] == cislice[j].znaky[b] - 32) {
                            pruchod = z;
                            splneno = 1;
                            validace++;
                            break;
                        }
                    }
                    if (splneno)
                        break;
                }
            }

            //Pokud předchozí cyklus znak našel tak následující část kódu kontroluje, zda jsou i navazující znaky
            //shodné se znaky kritéria
            if (splneno) {
                k++;
                while (kriterium[k] >= '0' && kriterium[k] <= '9') {
                    pruchod++;
                    if(kontakty[i].jmeno.arr[pruchod] != ' ') {
                        j = getCislici(cislice, kriterium[k]);

                        splneno = 0;
                        for (int b = 0; b < cislice[j].pocet_znaku; b++) {
                            if (kontakty[i].jmeno.arr[pruchod] == cislice[j].znaky[b] || kontakty[i].jmeno.arr[pruchod] == cislice[j].znaky[b] - 32) {
                                splneno = 1;
                                validace++;
                                break;
                            }
                        }

                        if (!splneno)
                            break;
                        k++;
                    }
                }
                //Pokud se vše shoduje zadá se kontakt k vypsání
                if (splneno && validace == prvku_kriteria) {
                    souradnice_nalezenych[pocet_nalezenych++] = i;
                    break;
                }
            }
        }

        //Pokud se neshoduje jméno kontaktu s kritériem a nebo kritérium obsahuje '0' nebo '1' nastává čas na tuto
        //část kódu, která funguje stejně jako ta výše, jen porovnává číslo kontaktu se zadaným kritériem
        if(!splneno){
            validace = 0;
            pruchod = 0;

            kolik_opakovani = getPocetOpakovaniCislo(kontakty[i].cislo, kriterium[0]);

            for(int a = 0; a < kolik_opakovani; a++) {
                validace = 0;
                splneno = 0;
                k = 0;

                //Najití pozice požadovaného znaku
                for (int z = pruchod; z < kontakty[i].cislo.delka; z++) {
                    if(kriterium[k] == '0'){
                        if (kontakty[i].cislo.arr[z] == '0' || kontakty[i].cislo.arr[z] == '+') {
                            pruchod = z;
                            splneno = 1;
                            validace++;
                            break;
                        }
                    }
                    else {
                        if (kontakty[i].cislo.arr[z] == kriterium[k]) {
                            pruchod = z;
                            splneno = 1;
                            validace++;
                            break;
                        }
                    }
                }
                //Kontrola zda i navazující znaky vyhovují kritériu
                if (splneno) {
                    k++;
                    while (kriterium[k] >= '0' && kriterium[k] <= '9') {
                        pruchod++;
                        splneno = 0;
                        if(kriterium[k] == '0'){
                            if (kontakty[i].cislo.arr[pruchod] == '0' || kontakty[i].cislo.arr[pruchod] == '+') {
                                splneno = 1;
                                validace++;
                            }
                        }
                        else {
                            if (kontakty[i].cislo.arr[pruchod] == kriterium[k]) {
                                splneno = 1;
                                validace++;
                            }
                        }
                        if(!splneno)
                            break;
                        k++;
                    }
                    //Pokud vše vyhovuje přidá se kontakt do seznamu k vypsání
                    if (splneno && validace == prvku_kriteria) {
                        souradnice_nalezenych[pocet_nalezenych++] = i;
                        break;
                    }
                }
            }
        }
    }
    //Pokud je počet nalezených záznamů více než 0 vypíší se, pokud ne vypíše se chybové hlášení
    if(pocet_nalezenych > 0) {
        for (int i = 0; i < pocet_nalezenych; i++) {
            vypisJednohoKontaktu(kontakty[souradnice_nalezenych[i]]);
        }
    }
    else {
        vypisNeprimePosloupnosti(kontakty, kriterium, cislice, celkem_kontaktu);
    }
}

//---------------------------------- Hlavní funkce ----------------------------------
int main(int argc, char *argv[]) {
    int pocet = kontrolaArgc(argc);

    if(pocet == 0) //Pokud je zadáno více nž 2 argumenty vypíše se chybová hláška
        fprintf(stderr, "Zadal si prilis mnoho argumentu, program se ukoncil\n");
    else {
        Kontakt kontakty[42];
        int celkem_kontaktu = naplneniKontaktu(kontakty);

        if(celkem_kontaktu == -1){
            fprintf(stderr, "Neplatny tvar cisla u nektereho kontaktu\n");
        }
        else if (pocet == 1) { //Pokud je zadán pouze defaultní argument vypíše se celý seznam
            //Výpis celého seznam
            vypisVsechKontaktu(kontakty, celkem_kontaktu);
        }
        else { //Pokud jsou zadány dva argumenty, tedy i kritérium vypíše se seznam podle něj
            if (kontrolaArgv(argv[1])) {
                //Výpis podle kritéria
                Cislice cislice[10];
                zalozeniCislic(cislice);

                vypisPrimePosloupnosti(kontakty, argv[1], cislice, celkem_kontaktu);
            }
            else { //Pokud je první znak argumentu něco jiného než číslice, další znaky program nerozpoznává,
                //pokud je tam něco jiného než číslice program tento znak bude ignorovat a i všechny znaky v kritériu za ním
                fprintf(stderr, "Zadal jsi neplatny tvar kriteria\n");
            }
        }
    }
    return 0;
}