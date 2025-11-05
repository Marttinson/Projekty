#include <iostream>

using namespace std;

int main() {
  //deklarace proměnných
  char hraci_pole[10][10];
  int vyhra = 0;
  char znak;
  bool dohrano = false;
  int pocet_kol = 1;
  int souradniceX;
  char X;
  int souradniceY = 0;
  int pocet_na_vyhru;

  //Naplnění pole
  hraci_pole[0][0] = ' ';

  //Dosazení Y osy
  for(int i = 1; i < 10; i++)
    hraci_pole[i][0] = i + '0';

  //Dosazení X osy
  for (int i = 1; i < 10; i++)
    hraci_pole[0][i] = i + 'A' - 1;

  //Dosazení prázdného místa do hracího pole
  for (int i = 1; i < 10; i++){
    for (int j = 1; j < 10; j++){
      hraci_pole[i][j] = ' ';
    }
  }

  //Zde hráč zadává do kolika chce hrát
  do  {
    cout << "Zadej na kolik chcete hrat: ";
    cin >> pocet_na_vyhru;
  } while (pocet_na_vyhru < 1 || pocet_na_vyhru > 6);

  //Výpis hracího pole
  for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        cout << hraci_pole[i][j];
        cout << "|";
      }
      cout << endl;
    }
  
  //Herni cyklus, cyklus běží, dokud běží hra
  do{
    //Rozhodnutí jaký hráč je na řadě, podle počtu kol
    if (pocet_kol % 2 == 1){
      cout << "Na rade je hrac s krizky\n";
      znak = 'X';
    }
    else{
      cout << "Na rade je hrac s kolecky\n";
      znak = 'O';
    }

    //Vstup souřadnic a kontrola, zda mají správnou hodnotu
    cout << "Zadej souradnice ve fromatu X a Y aby jsi vyplnil sve pole.\n";

    do{
      cout << "X: ";
      cin >> X;
      souradniceX = X - 'A' + 1;
    } while(souradniceX < 1 || souradniceX > 9);

    do{
    cout << "Y: ";
    cin >> souradniceY;
    } while(souradniceY < 1 || souradniceY > 9);

    hraci_pole[souradniceY][souradniceX] = znak;
    
    vyhra = 0;
    int x = 0;
    int y = 0;

    //Kontrola na vodorovné ose, zda jeden z hráčů nevyhrál
    x = souradniceX;
    y = souradniceY;

    while(hraci_pole[y][x] == znak){
      vyhra++;
      x--;
    }
    x = souradniceX + 1;
    while(hraci_pole[y][x] == znak){
      vyhra++;
      x++;
    }
    if(vyhra == pocet_na_vyhru)
      dohrano = true;

    //Kontrola na svislé ose, zda jeden z hráčů nevyhrál
    vyhra = 0;
    x = souradniceX;
    y = souradniceY;

    while(hraci_pole[y][x] == znak){
      vyhra++;
      y--;
    }
    y = souradniceY + 1;
    while(hraci_pole[y][x] == znak){
      vyhra++;
      y++;
    }
    if(vyhra == pocet_na_vyhru)
      dohrano = true;

    //Šikmá kontrola, zda jeden z hráčů nevyhrál
    vyhra = 0;
    x = souradniceX;
    y = souradniceY;

    while(hraci_pole[y][x] == znak){
      vyhra++;
      x++;
      y++;
    }
    x = souradniceX - 1;
    y = souradniceY - 1;
    while(hraci_pole[y][x] == znak){
      vyhra++;
      x--;
      y--;
    }
    if(vyhra == pocet_na_vyhru)
      dohrano = true;

    //Druhá šikmá kontrola, zda jeden z hráčů nevyhrál
    vyhra = 0;
    x = souradniceX;
    y = souradniceY;

    while(hraci_pole[y][x] == znak){
      vyhra++;
      x++;
      y--;
    }
    x = souradniceX - 1;
    y = souradniceY + 1;
    while(hraci_pole[y][x] == znak){
      vyhra++;
      x--;
      y++;
    }
    if(vyhra == pocet_na_vyhru)
      dohrano = true;

      
    //Výpis hracího pole, na konci každého kola
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        cout << hraci_pole[i][j];
        cout << "|";
      }
      cout << endl;
    }

    //Pokud jeden z hráčů vyhrál program se zeptá jestli má hru zopakovat, případně se ukončí
    if(dohrano){
      cout << "Vyhral hrac " << znak << endl;
      string volba;
      cout << "Chces hrat znovu? A / N: ";
      cin >> volba;
      if(volba == "A" || volba == "a"){
        dohrano = false;
        for (int i = 1; i < 10; i++){
          for (int j = 1; j < 10; j++){
            hraci_pole[i][j] = ' ';
            cout << "|";
          }
        }
        pocet_kol = 1;
      }

      //Výpis hracího pole
      for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
          cout << hraci_pole[i][j];
          cout << "|";
        }
        cout << endl;
      }
    }

    //Na konci každého kola se počet kol zvýší o 1
    pocet_kol++;
  } while(!dohrano);
} 