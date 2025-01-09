#ifndef HRAC
#define HRAC

#include "kralovstvo.h"


typedef struct hrac {
    char* meno_;
    kralovstvo* kralovstvo_;
    
}hrac;

typedef struct utok
{
    armada* armada_;
    char* menoObrancu_;
    char* menoUtociaceho_;
    int poctyVojakov_[POCET_DRUHOV_VOJAKOV];
}utok;


void zautoc(hrac* utocnik);

//TODO ked prebehne utok zmensit velkost armady utocnika aj obrancu
void branSa(hrac* utocnik, hrac* obranca);
void hracINIT(hrac* hracPar, char* cesta, char* meno);
void hracDestroy(hrac* hracPar);
void zacniHru();
void hraj(hrac* hracPar);
void ukonciHru(hrac* hracPar);
void hlavneMenu();
void vypisInformacieMenu();
void zvysovanieUrovneMenu();
void verbovanieMenu();
void prehra(hrac* hracPar);

#endif //HRAC_H
