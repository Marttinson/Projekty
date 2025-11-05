#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

int pocet_zakazniku;
int pocet_uredniku;
int max_cekani;
int max_prestavka;
int oteviraci_doba;

//Načtení vstupních argumentů do proměnných
int vstup(int argc, char* argv[]){
    if(argc != 6)
        return -1;

    pocet_zakazniku = atoi(argv[1]);
    pocet_uredniku = atoi(argv[2]);

    max_cekani = atoi(argv[3]);
    if(max_cekani < 0 || max_cekani > 10000)
        return -1;

    max_prestavka = atoi(argv[4]);
    if(max_prestavka < 0 || max_prestavka > 100)
        return -1;

    oteviraci_doba = atoi(argv[5]);
    if(oteviraci_doba < 0 || oteviraci_doba > 10000)
        return -1;

    return 1;
}

int main(int argc, char* argv[]) {
    //Pomoc ke generování náhodných čísel
    time_t t;
    srand((unsigned) time(&t));
    
    //Načítání vstupních dat z parametrů při spuštění, a jejich kontrola
    if(vstup(argc, argv) == -1){
        fprintf(stderr, "chybně zadané parametry.\n");
        return 1;
    }

    //Soubor
    FILE* file;
    file = fopen("proj2.out", "w");

    //------------------------------ Sdílená paměť ------------------------------
    //Pořadí - A
    int *poradi = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *poradi = 1;

    //Semafor, kontrolující změnu pořadí
    sem_t *sem_zmena_poradi = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(sem_zmena_poradi, 1, 1);

    //Proměnná určující zda je pošta otevřená
    uint8_t *posta_otevreno = mmap(NULL, sizeof(uint8_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *posta_otevreno = 1;

    //Semafor, kontrolující změnu pošty
    sem_t *sem_zmena_posty = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(sem_zmena_posty, 1, 1);

    //Počet dopisů - 1
    sem_t *dopisy = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(dopisy, 1, 0);

    //Počet balíků - 2
    sem_t *baliky = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(baliky, 1, 0);

    //Počet peněžních služeb - 3
    sem_t *penize = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(penize, 1, 0);

    //Úředníci
    sem_t *urednici = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(urednici, 1, 0);

    int *zakaznici = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *zakaznici = 0;

    //---------------------------- Základní proměnné ----------------------------
    int funkce = 1; //Zákkazník - 1
    int id = getpid();
    int idZ, idU;

    //-------------------------------- Vytváření --------------------------------
    //Vytváření zákazníků
    for(int i = 0; i < pocet_zakazniku; i++){
        if(id != 0){
            id = fork();
            idZ = i + 1;
        }
    }

    //Vytváření úředníků
    if(id != 0){
        funkce = 2; //Úředník - 2
        for(int i = 0; i < pocet_uredniku; i++){
            if(id != 0){
                id = fork();
                idU = i + 1;
            }
        }
    }
    //-------------------------------- Zákazník --------------------------------
    if(funkce == 1 && id == 0){
        sem_wait(sem_zmena_poradi);
        fprintf(file, "%d: Z %d: started\n", *poradi, idZ);
        fflush(file);
        *poradi += 1;
        sem_post(sem_zmena_poradi);

        int random = rand() % max_cekani + 1;
        usleep(random * 1000);
        
        //Kontrola jestli je zavřená pošta, pokud ano zákazník jde domů
        if(*posta_otevreno == 1){   //Pošta otevřená
            random = rand() % 3 + 1;

            sem_wait(sem_zmena_poradi);
            fprintf(file, "%d: Z %d: entering office for a service %d\n", *poradi, idZ, random);
            fflush(file);
            *poradi += 1;
            sem_post(sem_zmena_poradi);
            
            if(random == 1)
                sem_post(dopisy);
            else if(random == 2)
                sem_post(baliky);
            else
                sem_post(penize);
            
            sem_wait(urednici);
            sem_wait(sem_zmena_poradi);
            fprintf(file, "%d: Z %d: called by office worker\n", *poradi, idZ);
            fflush(file);
            *poradi += 1;
            sem_post(sem_zmena_poradi);

            usleep(rand() % 11);
        }

        sem_wait(sem_zmena_poradi);
        fprintf(file, "%d: Z %d: going home\n", *poradi, idZ);
        fflush(file);
        *poradi += 1;
        *zakaznici += 1;
        sem_post(sem_zmena_poradi);
    }
    //--------------------------------- Úředník ---------------------------------
    else if(funkce == 2 && id == 0){
        sem_wait(sem_zmena_poradi);
        fprintf(file, "%d: U %d: started\n", *poradi, idU);
        fflush(file);
        *poradi += 1;
        sem_post(sem_zmena_poradi);

        while(1){
            if(dopisy->__align > 0){    //Dopisy
                sem_wait(dopisy);
                sem_post(urednici);
                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: serving a service of type 1\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);

                usleep(rand() % 11);

                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: service finished\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);
            }
            else if(baliky->__align > 0){
                sem_wait(baliky);
                sem_post(urednici);
                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: serving a service of type 2\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);

                usleep(rand() % 11);

                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: service finished\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);
            }
            else if(penize->__align > 0){
                sem_wait(penize);
                sem_post(urednici);
                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: serving a service of type 3\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);

                usleep(rand() % 11);

                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: service finished\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);
            }
            else{
                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: taking break\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);

                usleep((rand() % max_prestavka) * 1000);

                sem_wait(sem_zmena_poradi);
                fprintf(file, "%d: U %d: break finished\n", *poradi, idU);
                fflush(file);
                *poradi += 1;
                sem_post(sem_zmena_poradi);
            }

            if(*posta_otevreno == 0 && *zakaznici == pocet_zakazniku)
                break;
        }

        sem_wait(sem_zmena_poradi);
        fprintf(file, "%d: U %d: going home\n", *poradi, idU);
        fflush(file);
        *poradi += 1;
        sem_post(sem_zmena_poradi);
    }
    //------------------------------ Hlavní proces ------------------------------
    else{
        int random;
        do{
            random = rand() % oteviraci_doba + 1;
        } while(random < oteviraci_doba / 2);
        usleep(random * 1000);

        sem_wait(sem_zmena_poradi);
        fprintf(file, "%d: closing\n", *poradi);
        fflush(file);
        *poradi += 1;
        sem_post(sem_zmena_poradi);

        sem_wait(sem_zmena_posty);
        *posta_otevreno = 0;
        sem_post(sem_zmena_posty);
    }

    while(wait(NULL) != -1);

    if(id != 0){
        sem_destroy(sem_zmena_poradi);
        sem_destroy(sem_zmena_posty);
        sem_destroy(dopisy);
        sem_destroy(baliky);
        sem_destroy(penize);
        sem_destroy(urednici);

        fclose(file);
    }

    return 0;
}