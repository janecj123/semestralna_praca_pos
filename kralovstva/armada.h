#ifndef ARMADA
#define ARMADA

#include "budova.h"

#define MAX_POCET_VOJAKOV 500


typedef struct vojak {
    typVojaka typ_;
    int cena_[POCET_DRUHOV_SUROVIN];
    int pocet_;
    int casVerbovania_;
}vojak;

typedef enum silaVojaka {
    KOPIJNIK_SILA_UTOKU = 1,
    SERMIAR_SILA_UTOKU,
    LUKOSTRELEC_SILA_UTOKU,
    KOPIJNIK_NA_KONI_SILA_UTOKU,
    LUKOSTRELEC_NA_KONI_SILA_UTOKU,
    SERMIAR_NA_KONI_SILA_UTOKU
} silaVojaka;


typedef struct prikazVerbovania {
    budovaArmada* budova_;
    typVojaka typ_;
    int pocet_;
      
} prikazVerbovania;

typedef struct armada{
    prikazVerbovania* buffer_;
    int pocetPrvokov_;
    int indexVkladania_;
    int indexVyberania_;
    int velkostArmady_;
    vojak vojaci_[POCET_DRUHOV_VOJAKOV];
    pthread_mutex_t mutex_;
    pthread_cond_t konzument_;

}armada;


void armadaINIT(armada* armadaPar);
void armadaDestroy(armada* armadaPar);
void vlozPrikazNaVerbovanieDoBuffera( budovaArmada* budova, typVojaka typ, int pocet, armada* armadaPar);
void* verbuj(void* armadaPar);



#endif //ARMADA