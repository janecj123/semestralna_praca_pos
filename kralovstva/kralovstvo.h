#ifndef KRALOVSTVO
#define KRALOVSTVO


#include <stdbool.h>
#include "armada.h"


typedef struct suroviny {
    int kamen_;
    int drevo_;
    int zelezo_;
    budovaObycajna* kamenolom_;
    budovaObycajna* drevorubac_;
    budovaObycajna* zeleziarne_;
    budovaObycajna* sklad_;
    atomic_bool koniecHry_;
    pthread_mutex_t mutex_;
    pthread_mutex_t* mutexVerbovisko_;
}suroviny;

typedef struct kralovstvo {
    budovaObycajna budovyObycajne_[POCET_BUDOV_OBYCAJNA];
    budovaArmada budovyArmady_[POCET_BUDOV_ARMADA];
    char** nazvyObycajnychBudov_;
    char** nazvyArmadnychBudov_;
    char** nazvyVojakov_;
    zvysovacUrovneBudovaObycajna zdielanyBufferObycajna_;
    zvysovacUrovneBudovaArmada zdielanyBufferArmada_;
    armada armada_;
    suroviny suroviny_;

    pthread_mutex_t mutexKralovstvo_;
    pthread_mutex_t mutexVerbovisko_;
    pthread_t vlaknoSuroviny_;
    pthread_t vlaknoPridavanieObycajnychBudov_;
    pthread_t vlaknoPridavanieArmadnychBudov_;
    pthread_t vlaknoArmady_;
} kralovstvo;




void kralovstvoINIT(kralovstvo* kralovstvoPar, char* cesta);
void kralovstvoDestroy(kralovstvo* kralovstvoPar);


void budovyObycajneINIT(kralovstvo* kralovstvoPar);
void budovyArmadyINIT(kralovstvo* kralovstvoPar);
void surovinyINIT(kralovstvo* kralovstvoPar);
void vojaciINIT(kralovstvo* kralovstvoPar);
void pociatoceHodnotyINIT(kralovstvo* kralovstvoPar, char* cesta);


void zvysUrovenObycajna(int hlavnaBudovaUroven, budovaObycajna* budovaNaVylepsenie, suroviny* kralovstvoPar, zvysovacUrovneBudovaObycajna* zvysovac);
void zvysUrovenArmadna(int hlavnaBudovaUroven, budovaArmada* budovaNaVylepsenie, suroviny* surovinyPar, zvysovacUrovneBudovaArmada* zvysovac);
bool daSaPridatObycajna(zvysovacUrovneBudovaObycajna* zvysovac);
bool daSaPridatArmadna(zvysovacUrovneBudovaArmada* zvysovac);
bool overDostatokSurovinAUrovenObycajna(suroviny* surovinyPar, budovaObycajna* budova);
bool overDostatokSurovinAUrovenArmadna(suroviny* surovinyPar, budovaArmada* budova);
void verbujNovychVojakov(budovaArmada* budova,int pocet, typVojaka typ ,suroviny* surovinyPar, armada* armadaPar);
bool daSaPridatVerbovanie(armada* armadaPar, budovaArmada* budova, typVojaka typ, int pocet);
bool overDostatokSurovinNaVerbovanie(suroviny* surovinyPar, armada* armadaPar, typVojaka typ, int pocet);
void* spravujSuroviny(void* surovinyPar);

void vypisInfoBudovy( kralovstvo* kralovstvoPar);
void vypisInfoVojsko( kralovstvo* kralovstvoPar);
void vypisInfoSuroviny(kralovstvo* kralovstvoPar);
void vypisInfoKralovstvo( kralovstvo* kralovstvoPar);
void vypisInfoKralovstvo(kralovstvo* kralovstvoPar);

#endif //KRALOVSTVO_H
