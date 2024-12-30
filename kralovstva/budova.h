#ifndef BUDOVA_H
#define BUDOVA_H

#include <unistd.h>

#define POCET_VOJAKOV_BUDOVA 3
#define KOEFICIENT_ZVYSOVANIE 5
#define KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA 3
#define MAX_UROVEN_HLAVNA_BUDOVA 25
#define MAX_UROVEN_KASARNE 15
#define MAX_UROVEN_OPEVNENIE 20
#define MAX_UROVEN_STAJNE 15
#define MAX_UROVEN_KOSTOL 3
#define MAX_UROVEN_KAMENOLOM 25
#define MAX_UROVEN_ZELEZIARNE 25
#define MAX_UROVEN_DREVORUBAC 25
#define MAX_UROVEN_VERBOVISKO 25
#define CAS_VERBOVANIA_SERMIAR 30
#define CAS_VERBOVANIA_KOPIJNIK 20
#define CAS_VERBOVANIA_LUKOSTRELEC 35
#define CAS_VERBOVANIA_LUKOSTRELEC_NA_KONI 60
#define CAS_VERBOVANIA_SERMIAR_NA_KONI 100
#define CAS_VERBOVANIA_KOPIJNIK_NA_KONI 70
#define POCET_BUDOV_OBYCAJNA 7
#define POCET_BUDOV_ARMADA 2
#define POCET_DRUHOV_VOJAKOV 6

typedef enum typBudovy {
    HLAVNA_BUDOVA,
    OPEVNENIE,
    KOSTOL,
    KAMENOLOM,
    DREVORUBAC,
    ZELEZIARNE,
    VERBOVISKO,
    KASARNE,
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

typedef struct vojak {
    typVojaka typ_;
    int pocet_;
}vojak;

typedef struct budovaObycajna {
    typBudovy typ_;
    int uroven_;
    int pocetZdrojov_;
    int maxUroven_;

}budovaObycajna;

typedef struct budovaArmada {
    typBudovy typ_;
    int uroven_;
    int maxUroven_;
    vojak armada_[POCET_VOJAKOV_BUDOVA];

}budovaArmada;

typedef struct zvysovacUrovneBudovaObycajna {
    budovaObycajna hlavnaBudova_;
    budovaObycajna budovaNaVylepsenie_;

}zvysovacUrovneBudovaObycajna;

typedef struct zvysovacUrovneBudovaArmada {
    budovaObycajna hlavnaBudova_;
    budovaArmada budovaNaVylepsenie_;

}zvysovacUrovneBudovaArmada;

typedef struct verbovacArmady {
    budovaArmada budova_;
    int pocet;
    typVojaka typ_;
}verbovacArmady;


void* zvysUrovenObycajnaBudova(void* zvysovacUrovne);
void* zvysUrovenArmadnaBudova(void* zvysovacUrovne);
void priradMaxUrovenObycajnaBudova(budovaObycajna* budova);
void priradMaxUrovenArmadnaBudova(budovaArmada* budova);
void* verbovanie (void* verbovac);


#endif //BUDOVA_H
