
#include "armada.h"
#include <stdio.h>
#include <stdlib.h>

void armadaINIT(armada* armadaPar) {
        
        armadaPar->buffer_ = calloc(VELKOST_BUFFERA_VERBOVANIA, sizeof(prikazVerbovania));
        armadaPar->pocetPrvokov_ = 0;
        armadaPar->indexVkladania_ = 0;
        armadaPar->indexVyberania_ = 0;
        armadaPar->velkostArmady_ = 0;
      

        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                armadaPar->vojaci_[i].pocet_ = 0;
                armadaPar->vojaci_[i].typ_ = i;
        }


        
        pthread_cond_init(&armadaPar->konzument_, NULL);
        pthread_mutex_init(&armadaPar->mutex_, NULL);

}

void armadaDestroy(armada* armadaPar){
        
        pthread_cond_destroy(&armadaPar->konzument_);
        pthread_mutex_destroy(&armadaPar->mutex_);
        free(armadaPar->buffer_);
}

void vlozPrikazNaVerbovanieDoBuffera(budovaArmada* budova, typVojaka typ, int pocet, armada* armadaPar){

        pthread_mutex_lock(&armadaPar->mutex_);
        
        armadaPar->buffer_[armadaPar->indexVkladania_].budova_ = budova;
        armadaPar->buffer_[armadaPar->indexVkladania_].typ_ = typ;
        armadaPar->buffer_[armadaPar->indexVkladania_].pocet_ = pocet;

        int cas = (armadaPar->vojaci_[typ].casVerbovania_ -  budova->uroven_) * pocet;
       
        printf("Prikaz uspesne pridany do radu na verbovanie.Cas verbovania: %d\n", cas);
        
        armadaPar->indexVkladania_ = (armadaPar->indexVkladania_ + 1) % VELKOST_BUFFERA_VERBOVANIA;
        armadaPar->pocetPrvokov_++;

        pthread_cond_signal(&armadaPar->konzument_);
        pthread_mutex_unlock(&armadaPar->mutex_);
}


//postupne verbuje vojakov ktory cakaju v rade na verbovanie
void* verbuj(void* armadaPar){

        armada* armada = armadaPar;
        while (true)
        {
                pthread_mutex_lock(&armada->mutex_);
                while (armada->pocetPrvokov_ == 0)
                {
                        pthread_cond_wait(&armada->konzument_, &armada->mutex_);
                }
                int cas = (armada->vojaci_[armada->buffer_[armada->indexVyberania_].typ_].casVerbovania_ - armada->buffer_[armada->indexVyberania_].budova_->uroven_ ) * armada->buffer_[armada->indexVyberania_].pocet_;
                pthread_mutex_unlock(&armada->mutex_);
                sleep(cas);
                pthread_mutex_lock(&armada->mutex_);
                
                armada->vojaci_[armada->buffer_[armada->indexVyberania_].typ_].pocet_ += armada->buffer_[armada->indexVyberania_].pocet_;
                
                armada->indexVyberania_ = (armada->indexVyberania_ + 1) % VELKOST_BUFFERA_VERBOVANIA;
                armada->pocetPrvokov_--;
                pthread_mutex_unlock(&armada->mutex_);
        }
        return NULL;
}