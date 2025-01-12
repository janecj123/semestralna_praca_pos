
#ifndef HRA
#define HRA

#include "zdielane_data.h"


void hraINIT(hrac* hracPar,zdielaneNazvy* nazvy, char* meno, char* cesta, hracVBufferi* hracVB);
void hraDestroy(zdielaneNazvy nazvy,hracVBufferi* hracVB);
void zacniHru(hrac* hracPar);
void hraj(hrac* hracPar);
void ukonciHru(hrac* hracPar, zdielaneNazvy nazvy);
void hlavneMenu();
void vypisInformacieMenu();
void zvysovanieUrovneMenu();
void verbovanieMenu();

void pridajUtok(hrac* utocnik);
void* aktualizujArmadu(void* arg);
void pridajHraca(zdielaneData* zd, zdielaneNazvy* nazvy, hrac* hracPar, hracVBufferi* hracVB);

#endif //HRA