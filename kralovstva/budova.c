#include "budova.h"





void* zvysUrovenObycajnaBudova(void* zvysovacUrovne) {
    zvysovacUrovneBudovaObycajna* zvysovac = zvysovacUrovne;

    sleep((zvysovac->budovaNaVylepsenie_.uroven_ * KOEFICIENT_ZVYSOVANIE) - (zvysovac->hlavnaBudova_.uroven_  * KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA));
    zvysovac->budovaNaVylepsenie_.uroven_++;

    return NULL;
}

void* zvysUrovenArmadnaBudova(void* zvysovacUrovne) {
    zvysovacUrovneBudovaArmada* zvysovac = zvysovacUrovne;

    sleep((zvysovac->budovaNaVylepsenie_.uroven_ * KOEFICIENT_ZVYSOVANIE) - (zvysovac->hlavnaBudova_.uroven_  * KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA));
    zvysovac->budovaNaVylepsenie_.uroven_++;

    return NULL;
}

void priradMaxUrovenObycajnaBudova(budovaObycajna* budova) {

    switch (budova->typ_) {
        case HLAVNA_BUDOVA:
            budova->maxUroven_ = MAX_UROVEN_HLAVNA_BUDOVA;
            break;
        case OPEVNENIE:
            budova->maxUroven_ = MAX_UROVEN_OPEVNENIE;
            break;
        case KOSTOL:
            budova->maxUroven_ = MAX_UROVEN_KOSTOL;
            break;
        case KAMENOLOM:
            budova->maxUroven_ = MAX_UROVEN_KAMENOLOM;
            break;
        case DREVORUBAC:
            budova->maxUroven_ = MAX_UROVEN_DREVORUBAC;
            break;
        case ZELEZIARNE:
            budova->maxUroven_ = MAX_UROVEN_ZELEZIARNE;
            break;
        case VERBOVISKO:
            budova->maxUroven_ = MAX_UROVEN_VERBOVISKO;
            break;
    }
}
void priradMaxUrovenArmadnaBudova(budovaArmada* budova) {

    switch (budova->typ_) {
        case KASARNE:
            budova->maxUroven_ = MAX_UROVEN_KASARNE;
        break;
        case STAJNE:
            budova->maxUroven_ = MAX_UROVEN_STAJNE;
        break;
    }
}

void* verbovanie (void* verbovac) {
    verbovacArmady* vb = verbovac;

    switch (vb->typ_) {
        case KOPIJNIK:
            sleep(CAS_VERBOVANIA_KOPIJNIK - vb->budova_.uroven_);
            break;
        case LUKOSTRELEC:
            sleep(CAS_VERBOVANIA_LUKOSTRELEC - vb->budova_.uroven_);
            break;
        case SERMIAR:
            sleep(CAS_VERBOVANIA_SERMIAR - vb->budova_.uroven_);
            break;
        case LUKOSTRELEC_NA_KONI:
            sleep(CAS_VERBOVANIA_LUKOSTRELEC_NA_KONI - vb->budova_.uroven_ * 2);
            break;
        case SERMIAR_NA_KONI:
            sleep(CAS_VERBOVANIA_SERMIAR_NA_KONI - vb->budova_.uroven_ * 2);
            break;
        case KOPIJNIK_NA_KONI:
            sleep(CAS_VERBOVANIA_KOPIJNIK_NA_KONI - vb->budova_.uroven_ * 2);
            break;
    }

    return NULL;
}