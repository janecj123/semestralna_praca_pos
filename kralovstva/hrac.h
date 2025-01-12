#ifndef HRAC
#define HRAC

#include "kralovstvo.h"
#include "zdielane_nazvy.h"

#define MAX_DLZKA_MENA 20

typedef struct hrac {
    char meno_[MAX_DLZKA_MENA];
    kralovstvo* kralovstvo_;
    int id_;
    zdielaneNazvy nazvy_;
    atomic_bool koniecHry_;
    pthread_t vlakno_;
    atomic_bool prehra_;
}hrac;


typedef struct utok
{
    char menoObrancu_[MAX_DLZKA_MENA];
    char menoUtociaceho_[MAX_DLZKA_MENA];
    int poctyVojakov_[POCET_DRUHOV_VOJAKOV];
    int velkostArmady_;
    
}utok;

typedef struct hracVBufferi {
    char meno_[MAX_DLZKA_MENA];
    int zmenaVelkosti_;
    
    

}hracVBufferi;


void hracINIT(hrac* hracPar, char* cesta, char* meno, zdielaneNazvy* nazvy);
void hracDestroy(hrac* hracPar);


#endif //HRAC
