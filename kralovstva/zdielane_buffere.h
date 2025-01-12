
#ifndef ZDIELANE_BUFFERE
#define ZDIELANE_BUFFERE

#include "hrac.h"
#include <stdatomic.h>

#define MAX_POCET_HRACOV 5
#define MAX_POCET_UTOKOV 10




typedef struct zdielaneBuffere 
{
    hracVBufferi bufferHraci_[MAX_POCET_HRACOV];
    utok bufferUtoky_[MAX_POCET_UTOKOV]; 
    int pocetPrvkovVHraci_;
    int pocetPrvkovVUtoky_;
    int indexVkladaniaHraci_;
    int indexVkladaniaUtoky_;
    int indexVyberaniaUtoky_;
    atomic_bool ukonciServer_;
    

}zdielaneBuffere;



void zdielaneBuffereINIT(zdielaneBuffere* buffere);
void vlozHracaDoBuffera(zdielaneBuffere* buffere, hracVBufferi* hracPar, hrac* hracVkladany);
void vlozUtokDoBuffera(zdielaneBuffere* buffere, utok* utokPar);
void vyberHracaZBuffera(zdielaneBuffere* buffere, char* meno);
void vyberUtokZBuffera(zdielaneBuffere* buffere, utok* utokPar);
void najdiHracaVBuffery(zdielaneBuffere* buffere, bool* bolNajdeny, hracVBufferi* hracHladany, char* meno);
int najdiInexHracaVBuffery(zdielaneBuffere* buffere, char* meno);


#endif //ZDIELANE_BUFFERE