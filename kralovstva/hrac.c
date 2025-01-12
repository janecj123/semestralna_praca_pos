#include "hrac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void hracINIT(hrac* hracPar, char* cesta, char* meno, zdielaneNazvy* nazvy) {

    kralovstvo* k = malloc(sizeof(kralovstvo));
    hracPar->kralovstvo_ = k;
    hracPar->koniecHry_ = ATOMIC_VAR_INIT(false);
    hracPar->prehra_ = ATOMIC_VAR_INIT(false);
    hracPar->nazvy_ = *nazvy;
    strcpy(hracPar->meno_, meno);
    kralovstvoINIT(hracPar->kralovstvo_, cesta); 

}

void hracDestroy(hrac* hracPar){

    kralovstvoDestroy(hracPar->kralovstvo_);
    free(hracPar->kralovstvo_);
    
}

