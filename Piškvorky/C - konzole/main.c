#include <stdio.h>

int main(void) {
    char pole[10][10];
    char x, y;
    int i, j;
    int vyber = 1;
    int a = 0;
    int souradnice_x, souradnice_y;
    int pocet_her;
    
    for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++) {      //vynulovani pole pred pouzitim
                    pole[i][j] = ' ';
                }
     }
    for (j = 1; j < 10; j++)    //doplneni osy x
            pole[0][j] = 'A' + j - 1;

    for (i = 1; i < 10; i++)    //doplneni osy y
            pole[i][0] = '1' + i - 1;

    printf("Na kolik hrajete: ");
    scanf("%d", &pocet_her);

    do {

        for (i = 0; i < 10; i++) {
             for (j = 0; j < 10; j++) {  //vypsani hraci plochy
             printf("%c", pole[i][j]);
             }
             printf("\n");
             }
        if (a >= pocet_her * 2 -1) {
            printf("Pro skonceni stiskni '0', pro pokracovani cokoliv jinyho: ");
            scanf("%d", &vyber);   //ukonceni
        }
        if (vyber != 0) {

            

            if (a % 2 == 0) {
                printf("Na rade je hrac s krizky\n");

                printf("Zadej souradnici na ose x: ");
                scanf(" %c", &x);

                printf ("Zadej souradnici na ose y: ");  //krizky
                scanf(" %c", &y);

                souradnice_x = (int) x;
                souradnice_y = (int) y;

                souradnice_x -= 'A' - 1;
                souradnice_y -= '1' - 1;

                if(pole[souradnice_y][souradnice_x] == ' ' && souradnice_x <= 10 && souradnice_x >= 1 && souradnice_y <= 10 && souradnice_y >= 1){
                    pole[souradnice_y][souradnice_x] = 'X';
                }
                else {
                    a--;
                    printf("Obsazene pole, nebo neplatna hodnata. Zadej jinou hodnotu!\n");
                }
            }
            else {
                printf("Na rade je hrac s kolecky\n");

                printf("Zadej souradnici na ose x: ");
                scanf(" %c", &x);

                printf ("Zadej souradnici na ose y: ");  //kolecka
                scanf(" %c", &y);

                souradnice_x = (int) x;
                souradnice_y = (int) y;

                souradnice_x -= 'A' - 1;
                souradnice_y -= '1' - 1;

                if (pole[souradnice_y][souradnice_x] == ' ' && souradnice_x <= 10 && souradnice_x >= 1 && souradnice_y <= 10 && souradnice_y >= 1) {
                    pole[souradnice_y][souradnice_x] = 'O';
                }
                else {
                    a--;
                    printf("Obsazene pole, nebo neplatna hodnata. Zadej jinou hodnotu!\n");
                }
            }




            a++;
        }
    } while (vyber != 0);

    return 0;
}