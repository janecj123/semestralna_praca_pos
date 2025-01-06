#ifndef KRALOVSTVO_H
#define KRALOVSTVO_H


#include <stdbool.h>
#include "armada.h"


typedef struct kralovstvo {
    budovaObycajna budovyObycajne_[POCET_BUDOV_OBYCAJNA];
    budovaArmada budovyArmady_[POCET_BUDOV_ARMADA];
    suroviny suroviny_;
    char** nazvyObycajnychBudov_;
    char** nazvyArmadnychBudov_;
    char** nazvyVojakov_;
    zvysovacUrovneBudovaObycajna zdielanyBufferObycajna_;
    zvysovacUrovneBudovaArmada zdielanyBufferArmada_;
    pthread_mutex_t mutex_;
    armada armada_;
} kralovstvo;




void kralovstvoINIT(kralovstvo* kralovstvoPar, char* cesta, pthread_t* vlaknoSuroviny, pthread_t* vlaknoPridavanieObycajnychBudov, pthread_t* vlaknoPridavanieArmadnychBudov, pthread_t* vlaknoArmady);
void kralovstvoDestroy(kralovstvo* kralovstvoPar,  pthread_t vlaknoSuroviny, pthread_t vlaknoPridavanieObycajnychBudov, pthread_t vlaknoPridavanieArmadnychBudov, pthread_t vlaknoArmady);
void zvysovacUrovneObycajnaDestroy(zvysovacUrovneBudovaObycajna* zvysovac);
void zvysovacUronveArmadnaDestroy(zvysovacUrovneBudovaArmada* zvysovac);
void armadaDestroy(armada* armadaPar);
void budovyObycajneINIT( kralovstvo*   kralovstvoPar);
void budovyArmadyINIT( kralovstvo*  kralovstvoPar);
void pociatoceHodnotyINIT(kralovstvo* kralovstvoPar, char* cesta);
void vojaciINIT(kralovstvo* kralovstvoPar);
void zvysovacUrovneObycajnaINIT(int hlavnaBudovaUroven, zvysovacUrovneBudovaObycajna* zvysovac);
void zvysovacUrovneArmadnaINIT(int hlavnaBudovaUroven, zvysovacUrovneBudovaArmada* zvysovac);
void zvysUrovenObycajna(int hlavnaBudovaUroven, budovaObycajna* budovaNaVylepsenie, kralovstvo* kralovstvoPar);
void zvysUrovenArmadna(int hlavnaBudovaUroven, budovaArmada* budovaNaVylepsenie, kralovstvo* kralovstvoPar);
bool daSaPridatObycajna(zvysovacUrovneBudovaObycajna* zvysovac);
bool daSaPridatArmadna(zvysovacUrovneBudovaArmada* zvysovac);
bool overDostatokSurovinAUrovenObycajna(kralovstvo* kralovstvoPar, budovaObycajna* budova);
bool overDostatokSurovinAUrovenArmadna(kralovstvo* kralovstvoPar, budovaArmada* budova);
bool daSaPridatVerbovanie(armada* armadaPar, budovaArmada* budova, typVojaka typ);
bool overDostatokSurovinNaVerbovanie(suroviny* surovinyPar, armada* armadaPar, typVojaka typ, int pocet);
void verbujNovychVojakov(budovaArmada* budova,int pocet, typVojaka typ ,suroviny* surovinyPar, armada* armadaPar);

void vypisInfoBudovy( kralovstvo* kralovstvoPar);
void vypisInfoVojsko( kralovstvo* kralovstvoPar);
void vypisInfoSuroviny(kralovstvo* kralovstvoPar);
void vypisInfoKralovstvo( kralovstvo* kralovstvoPar);
void vypisInfoKralovstvo(kralovstvo* kralovstvoPar);

#endif //KRALOVSTVO_H
