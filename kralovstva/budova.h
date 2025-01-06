#ifndef BUDOVA_H
#define BUDOVA_H


#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define POCET_VOJAKOV_BUDOVA 3
#define KOEFICIENT_ZVYSOVANIE 5
//sluzi na vypocet o kolko sa skrati cas vylepsenia budov
#define KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA 2
#define KOEFICIENT_ZVYSOVANIE_SUROVIN 2

#define MAX_UROVEN_HLAVNA_BUDOVA 15
#define MAX_UROVEN_KASARNE 15
#define MAX_UROVEN_OPEVNENIE 20
#define MAX_UROVEN_STAJNE 15
#define MAX_UROVEN_KOSTOL 3
#define MAX_UROVEN_KAMENOLOM 25
#define MAX_UROVEN_ZELEZIARNE 25
#define MAX_UROVEN_DREVORUBAC 25
#define MAX_UROVEN_VERBOVISKO 25


#define CAS_SPRACOVANIE_SUROVIN 5

#define POCET_BUDOV_OBYCAJNA 7
#define POCET_BUDOV_ARMADA 2
#define POCET_DRUHOV_VOJAKOV 6
#define POCET_DRUHOV_SUROVIN 3

#define VELKOST_BUFFERA_VYLEPSOVANIA 3
#define VELKOST_BUFFERA_VERBOVANIA 5

typedef enum typBudovy {
    HLAVNA_BUDOVA,
    OPEVNENIE,
    KOSTOL,
    KAMENOLOM,
    DREVORUBAC,
    ZELEZIARNE,
    VERBOVISKO,
    KASARNE = 0,
    STAJNE

}typBudovy;

typedef enum typVojaka {
    KOPIJNIK,
    SERMIAR,
    LUKOSTRELEC,
    KOPIJNIK_NA_KONI,
    LUKOSTRELEC_NA_KONI,
    SERMIAR_NA_KONI

} typVojaka;



typedef struct budovaObycajna {
    typBudovy typ_;
    int uroven_;
    //sluzi na vypocet cas vylepsovania budovy pri vkladani do buffera na vylepsenie
    int urovenPreCas_;
    int maxUroven_;
    int cena_[POCET_DRUHOV_SUROVIN];
    int pocetZdrojov_;
    bool jeVBufferi_;
}budovaObycajna;

typedef struct budovaArmada {
    typBudovy typ_;
    int uroven_;
     //sluzi na vypocet cas vylepsovania budovy pri vkladani do buffera na vylepsenie
    int urovenPreCas_;
    int maxUroven_;
    int cena_[POCET_DRUHOV_SUROVIN];
    typVojaka typVojaka_[POCET_VOJAKOV_BUDOVA];
    bool jeVBufferi_;

}budovaArmada;

typedef struct zvysovacUrovneBudovaObycajna {
    int hlavnaBudovaUroven_;
    budovaObycajna** buffer_;
     //velkost a index buffera
    int pocetPrvokov_;
    int indexVkladania_;
    int indexVyberania_;
    
    atomic_bool koniecHry_;
    pthread_cond_t producent_;
    pthread_cond_t konzument_;
    pthread_mutex_t mutex_;

}zvysovacUrovneBudovaObycajna;

typedef struct zvysovacUrovneBudovaArmada {
    int hlavnaBudovaUroven_;
    budovaArmada** buffer_;
    //velkost a index buffera
    int pocetPrvokov_;
    int indexVkladania_;
    int indexVyberania_;
        

    atomic_bool koniecHry_;
    pthread_cond_t producent_;
    pthread_cond_t konzument_;
    pthread_mutex_t mutex_;

}zvysovacUrovneBudovaArmada;



typedef struct suroviny {
    int kamen_;
    int drevo_;
    int zelezo_;
    budovaObycajna kamenolom_;
    budovaObycajna drevorubac_;
    budovaObycajna zeleziarne_;
    atomic_bool koniecHry_;
    pthread_mutex_t mutex_;
}suroviny;




void priradMaxUrovenObycajnaBudova(budovaObycajna* budova);
void priradMaxUrovenArmadnaBudova(budovaArmada* budova);
void* verbovanie (void* verbovac);
void vylepsiBudovuObycajnu(budovaObycajna* budova, zvysovacUrovneBudovaObycajna* zvysovac);
void vylepsiBudovuArmadnu(budovaArmada* budova, zvysovacUrovneBudovaArmada* zvysovac);
void vlozObycajnuBudovuDoBuffera(zvysovacUrovneBudovaObycajna* zvysovac, budovaObycajna* budovaNaVylepseni);
void vlozArmadnuBudovuDoBuffera(zvysovacUrovneBudovaArmada* zvysovacUrovne, budovaArmada* budovaNaVylepsenie);
void* zvysUrovenObycajnaBudova(void* zvysovacUrovne);
void* zvysUrovenArmadnaBudova(void* zvysovacUrovne);
void* spravujSuroviny(void* surovinyPar);


#endif //BUDOVA_H
