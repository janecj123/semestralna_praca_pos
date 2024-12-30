#ifndef KRALOVSTVO_H
#define KRALOVSTVO_H

#include "budova.h"




typedef struct kralovstvo {
    budovaObycajna budovyObycajne_[POCET_BUDOV_OBYCAJNA];
    budovaArmada budovyArmady_[POCET_BUDOV_ARMADA];
    
    char** nazvyObycajnychBudov_;
    char** nazvyArmadnychBudov_;
    char** nazvyVojakov_;

} kralovstvo;


void kralovstvoINIT(kralovstvo* kralovstvoPar);
void kralovstvoDestroy(kralovstvo* kralovstvoPar);
char* alokujNazov(char* nazov);
void budovyObycajneINIT( kralovstvo*   kralovstvoPar);
void budovyArmadyINIT( kralovstvo*  kralovstvoPar);
void armadyINIT(kralovstvo*   kralovstvoPar);
void vypisInfoBudovy(const kralovstvo* kralovstvoPar);
void vypisInfoVojsko(const kralovstvo* kralovstvoPar);
void vypisInfoKralovstvo(const kralovstvo* kralovstvoPar);
#endif //KRALOVSTVO_H
