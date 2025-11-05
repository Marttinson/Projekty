#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

char* zvetseniCharu(char* pole, int pocet_prvku, int velikost_pole){//zvetseni ukazatele na char
  char *pomoc;
  pomoc = malloc(sizeof(char) * velikost_pole);
  for(int i = 0; i < pocet_prvku; i++){
    pomoc[i] = pole[i];
  }
  free(pole);
  pole = malloc(sizeof(char) * velikost_pole*2);
  for(int i = 0; i < pocet_prvku; i++){
    pole[i] = pomoc[i];
  }
  free(pomoc);

  return pole;
}

double* zvetseniDouble(double* pole, int pocet_prvku, int velikost_pole){//zvetseni ukazatele na double
  double* pomoc = malloc(sizeof(double) * velikost_pole);
  for(int i = 0; i < pocet_prvku; i++){
    pomoc[i] = pole[i];
  }
  free(pole);
  pole = malloc(sizeof(double) * velikost_pole * 2);
  for(int i = 0; i < pocet_prvku; i++){
    pole[i] = pomoc[i];
  }
  free(pomoc);

  return pole;
}

double soucet(double a, double b){
  return a + b;
}

double rozdil(double a, double b){
  return a - b;
}

double soucin(double a, double b){
  return a * b;
}

double podil(double a, double b){
    return a / b;
}

int main(void) {
  char* znaky = malloc(sizeof(char));
  int znaky_pocet_prvku = 0;
  int znaky_velikost_pole = 1;

  double cislo1 = 0;
  char* znaky_cisla1 = malloc(sizeof(char));
  int cislo1_pocet_prvku = 0;
  int cislo1_velikost_pole = 1;
  int pozice_tecky1;
  bool je_tam_tecka1 = false;

  double cislo2 = 0;
  char* znaky_cisla2 = malloc(sizeof(char));
  int cislo2_pocet_prvku = 0;
  int cislo2_velikost_pole = 1;
  int pozice_tecky2;
  bool je_tam_tecka2 = false;

  double* vysledek = malloc(sizeof(double));
  int vysledek_pocet_prvku = 0;
  int vysledek_velikosot_pole = 1;

  bool zadal = false;
  char znamenko;
  sem:
  printf("NASA Kalkulacka\nZadej priklad pro vypocitani\nKalkulacka umi scitat(+), odcitat(-), delit(/) a nasobit(*)\n");
    int i = 0;
    int j = 0;
    do{//nacteni prikladu
      if(znaky_pocet_prvku == znaky_velikost_pole){
        zvetseniCharu(znaky, znaky_pocet_prvku, znaky_velikost_pole);
        znaky_velikost_pole *= 2;
      }
      scanf("%c", &znaky[znaky_pocet_prvku]);
      znaky_pocet_prvku++;
    }while(znaky[znaky_pocet_prvku - 1] != 10);


    while(znaky[i] != 10){
      if(znaky[i] == '+' || znaky[i] == '-' || znaky[i] == '*' || znaky[i] == '/'){//rozdeleni podle znamenka
        zadal = true;
        znamenko = znaky[i];
      }
      else if(!zadal && ((znaky[i] >= '0' && znaky[i] <= '9') || znaky[i] == '.')){//1. cislo
        if(cislo1_pocet_prvku == cislo1_velikost_pole){//volani funkce kdyz je ukazatel plnej
          znaky_cisla1 = zvetseniCharu(znaky_cisla1, cislo1_pocet_prvku, cislo1_velikost_pole);
          cislo1_velikost_pole *= 2;
        }
        znaky_cisla1[i] = znaky[i];
        cislo1_pocet_prvku++;

        if(znaky[i] == '.'){
          pozice_tecky1 = i;
          je_tam_tecka1 = true;
        }
        else if(!je_tam_tecka1)
          pozice_tecky1 = cislo1_pocet_prvku;
      }
      else if(zadal && ((znaky[i] >= '0' && znaky[i] <= '9') || znaky[i] == '.')){//2.cislo
        if(cislo2_pocet_prvku == cislo2_velikost_pole){//volani funkce kdyz je ukazatel plnej
          znaky_cisla2 = zvetseniCharu(znaky_cisla2, cislo2_pocet_prvku, cislo2_velikost_pole);
          cislo2_velikost_pole *= 2;
        }
        znaky_cisla2[j] = znaky[i];
        cislo2_pocet_prvku++;
        j++;

        if(znaky[i] == '.'){
          pozice_tecky2 = j - 1;
          je_tam_tecka2 = true;
        }
        else if(!je_tam_tecka2)
          pozice_tecky2 = cislo2_pocet_prvku;
      }
      else{
        printf("Zadal si blbost, zkus to znovu\n");
        goto sem;
      }
      i++;
    }
    j = 0;
    for(i = 0; i < cislo1_pocet_prvku; i++){//prevod 1. cisla z charu na double
      if(znaky_cisla1[i] != '.'){
        cislo1 += (znaky_cisla1[i] - '0') * pow(10, pozice_tecky1 - j - 1);
        j++;
      }
    }

    j = 0;
    for(i = 0; i < cislo2_pocet_prvku; i++){//prevod 2. cisla z charu na double
      if(znaky_cisla2[i] != '.'){
        cislo2 += (znaky_cisla2[i] - '0') * pow(10, pozice_tecky2 - j - 1);
        j++;
      }
    }

    if(znamenko == '+'){
      vysledek[0] = soucet(cislo1, cislo2);
      vysledek_pocet_prvku++;
    }
    else if(znamenko == '-'){
      vysledek[0] = rozdil(cislo1, cislo2);
      vysledek_pocet_prvku++;
    }
    else if(znamenko == '*'){
      vysledek[0] = soucin(cislo1, cislo2);
      vysledek_pocet_prvku++;
    }
    else if(znamenko == '/'){
      /*double pomoc;
      if(cislo2 != 0){*/
        vysledek[0] = podil(cislo1, cislo2);
        vysledek_pocet_prvku++;
      /*}
      else{
        tady:
          printf("Nulou nelze delit, zadej jine cislo: ");
          scanf("%lf", &pomoc);
          if(pomoc == 0)
            goto tady;
          else{
            vysledek[0] = podil(cislo1, pomoc);
            vysledek_pocet_prvku++;
          }
      }*/
    }

    //tady zacinaji dalsi kola
    int k = 0;

    char* znaky_cisla = malloc(sizeof(char));
    int cislo_velikost_pole = 1;
    int cislo_pocet_prvku = 0;

    double cislo;
    int pozice_tecky;
    bool je_tam_tecka = false;

    do{
      here:
      free(znaky);
      znaky = malloc(sizeof(char));
      znaky_pocet_prvku = 0;
      znaky_velikost_pole = 1;

      free(znaky_cisla);
      znaky_cisla = malloc(sizeof(char));
      cislo_pocet_prvku = 0;
      cislo_velikost_pole = 1;

      cislo = 0;
      je_tam_tecka = false;
      
      printf("%f", vysledek[k]);

      do{//nacteni prikladu
      if(znaky_pocet_prvku == znaky_velikost_pole){
        zvetseniCharu(znaky, znaky_pocet_prvku, znaky_velikost_pole);
        znaky_velikost_pole *= 2;
      }
      
      scanf("%c", &znaky[znaky_pocet_prvku]);
      znaky_pocet_prvku++;
    }while(znaky[znaky_pocet_prvku - 1] != 10);

    j = 0;
    i = 0;
    while(znaky[j] != 10){
      if(znaky[j] == '+' || znaky[j] == '-' || znaky[j] == '*' || znaky[j] == '/'){
        znamenko = znaky[j];
      }
      else if((znaky[j] >= '0' && znaky[j] <= '9') || znaky[j] == '.' || znaky[j] == 'e'){
        if(cislo_velikost_pole == cislo_pocet_prvku){
          znaky_cisla = zvetseniCharu(znaky_cisla, cislo_pocet_prvku, cislo_velikost_pole);
          cislo_velikost_pole *= 2;
        }
        znaky_cisla[i] = znaky[j];
        cislo_pocet_prvku++;

        if(znaky[j] == '.'){
          pozice_tecky = j - 1;
          je_tam_tecka = true;
        }
        else if(!je_tam_tecka)
          pozice_tecky = cislo_pocet_prvku;
        i++;
      }
      else{
        printf("Zadal si blbost, zkus to znovu\n");
        goto here;
      }
      j++;
    }
    j = 0;
    for(i = 0; i < cislo_pocet_prvku; i++){//prevod cisla z charu na double
      if(znaky_cisla[i] != '.'){
        cislo += (znaky_cisla[i] - '0') * pow(10, pozice_tecky - j - 1);
        j++;
      }
    }

    if(vysledek_pocet_prvku == vysledek_velikosot_pole){
      vysledek = zvetseniDouble(vysledek, vysledek_pocet_prvku, vysledek_velikosot_pole);
      vysledek_velikosot_pole *= 2;
    }
    if(znamenko == '+'){
      vysledek[k+1] = soucet(vysledek[k], cislo);
      vysledek_pocet_prvku++;
    }
    else if(znamenko == '-'){
      vysledek[k+1] = rozdil(vysledek[k], cislo);
      vysledek_pocet_prvku++;
    }
    else if(znamenko == '*'){
      vysledek[k+1] = soucin(vysledek[k], cislo);
      vysledek_pocet_prvku++;
    }
    else if(znamenko == '/'){
      //if(cislo != 0){
        vysledek[k+1] = podil(vysledek[k], cislo);
        vysledek_pocet_prvku++;
      /*}
      else{
        double pomoc;
        do{
          printf("Nulou nelze delit, zadej jine cislo: ");
          scanf("%lf", &pomoc);
        }while(pomoc == 0);
        vysledek[k+1] = podil(vysledek[k], pomoc);
        vysledek_pocet_prvku++;
        
      }*/
    }

    k++;
    }while(znaky[0] != 'e');

  free(znaky_cisla1);
  free(znaky_cisla2);
  free(znaky_cisla);
  free(znaky);
  free(vysledek);
  return 0;
}
