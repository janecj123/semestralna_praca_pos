#ifndef HRAC_H
#define HRAC_H

#include "kralovstvo.h"


typedef struct hrac {
    char* meno_;
    kralovstvo* kralovstvo_;
    pthread_t* vlaknoSuroviny_;
    pthread_t* vlaknoPridavanieObycajnychBudov_;
    pthread_t* vlaknoPridavanieArmadnychBudov_;
    pthread_t* vlaknoArmady_;
}hrac;


void hracINIT(hrac* hracPar, char* cesta, char* meno);
void hlavneMenu();
void hracDestroy(hrac* hracPar);
void vypisInformacieMenu();
void zvysovanieUrovneMenu();
void verbovanieMenu();
void zacniHru();
void hraj(hrac* hracPar);
void ukonciHru(hrac* hracPar);

#endif //HRAC_H
