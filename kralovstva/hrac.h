#ifndef HRAC_H
#define HRAC_H

#include "kralovstvo.h"

typedef struct hrac {
    char* meno_;
    kralovstvo* kralovstvo_;
}hrac;


void hracINIT(hrac* hracPar);
#endif //HRAC_H
