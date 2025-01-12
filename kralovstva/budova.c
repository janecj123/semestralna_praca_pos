#include "budova.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

void zvysovacUrovneObycajnaINIT(int hlavnaBudovaUroven, zvysovacUrovneBudovaObycajna* zvysovac, pthread_mutex_t* mutexVerbovisko) {

        zvysovac->hlavnaBudovaUroven_ = hlavnaBudovaUroven;
        zvysovac->buffer_ = calloc(VELKOST_BUFFERA_VYLEPSOVANIA, sizeof(budovaObycajna));
        zvysovac->koniecHry_ = false;
        zvysovac->pocetPrvokov_ = 0;
        zvysovac->indexVkladania_ = 0;
        zvysovac->indexVyberania_ = 0;
        zvysovac->mutexVerbovisko_ = mutexVerbovisko;

        pthread_cond_init(&zvysovac->producent_, NULL);
        pthread_mutex_init(&zvysovac->mutex_, NULL);

}
void zvysovacUrovneArmadnaINIT(int hlavnaBudovaUroven, zvysovacUrovneBudovaArmada* zvysovac){

        zvysovac->hlavnaBudovaUroven_ = hlavnaBudovaUroven;
        zvysovac->buffer_ = calloc(VELKOST_BUFFERA_VYLEPSOVANIA, sizeof(budovaArmada));
        zvysovac->koniecHry_ = false;
        zvysovac->pocetPrvokov_ = 0;
        zvysovac->indexVkladania_ = 0;
        zvysovac->indexVyberania_ = 0;


        pthread_cond_init(&zvysovac->producent_, NULL);
        pthread_mutex_init(&zvysovac->mutex_, NULL);

}


void zvysovacUrovneObycajnaDestroy(zvysovacUrovneBudovaObycajna* zvysovac){
        
       
        free(zvysovac->buffer_);
        pthread_cond_destroy(&zvysovac->producent_);
        pthread_mutex_destroy(&zvysovac->mutex_);
}
void zvysovacUronveArmadnaDestroy(zvysovacUrovneBudovaArmada* zvysovac){
        
        
        free(zvysovac->buffer_);
        pthread_cond_destroy(&zvysovac->producent_);
        pthread_mutex_destroy(&zvysovac->mutex_);
}



void priradMaxUrovenObycajnaBudova(budovaObycajna* budova) {

    switch (budova->typ_) {
        case HLAVNA_BUDOVA:
            budova->maxUroven_ = MAX_UROVEN_HLAVNA_BUDOVA;
            break;
        case OPEVNENIE:
            budova->maxUroven_ = MAX_UROVEN_OPEVNENIE;
            break;
        case SKLAD:
            budova->maxUroven_ = MAX_UROVEN_SKLAD;
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
        case KOSTOL:
            budova->maxUroven_ = MAX_UROVEN_KOSTOL;
            break;
        default:
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
    default:
        break;
    }
}


void vlozObycajnuBudovuDoBuffera(zvysovacUrovneBudovaObycajna* zvysovac, budovaObycajna* budovaNaVylepsenie){
   
        pthread_mutex_lock(&zvysovac->mutex_);

        zvysovac->buffer_[zvysovac->indexVkladania_] = budovaNaVylepsenie;
        int cas = (zvysovac->buffer_[zvysovac->indexVkladania_]->urovenPreCas_ * KOEFICIENT_ZVYSOVANIE) - 
        (zvysovac->hlavnaBudovaUroven_ * KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA);
         
         if (cas < 0)
        {
            cas = 0; 
        }
        
        printf("Budova uspesne pridana do radu na zvysovanie. Cas tvania vylepsovania:  %d\n",cas);   
        zvysovac->buffer_[zvysovac->indexVkladania_]->urovenPreCas_++;

        //nastavi cenu dalsieho vylepsenia
        for(int i = 0; i < POCET_DRUHOV_SUROVIN; i++){
        zvysovac->buffer_[zvysovac->indexVyberania_]->cena_[i] += (10 * zvysovac->buffer_[zvysovac->indexVyberania_]->urovenPreCas_);
        }
       
        zvysovac->indexVkladania_ = (zvysovac->indexVkladania_ + 1) % VELKOST_BUFFERA_VYLEPSOVANIA;
        zvysovac->pocetPrvokov_++;
      
        pthread_cond_signal(&zvysovac->producent_);
        pthread_mutex_unlock(&zvysovac->mutex_);
        
    
  
}
void vlozArmadnuBudovuDoBuffera(zvysovacUrovneBudovaArmada* zvysovac, budovaArmada* budovaNaVylepsenie){
    
        pthread_mutex_lock(&zvysovac->mutex_);
       
        zvysovac->buffer_[zvysovac->indexVkladania_] = budovaNaVylepsenie;
        int cas = (zvysovac->buffer_[zvysovac->indexVkladania_]->urovenPreCas_ * KOEFICIENT_ZVYSOVANIE) - 
        (zvysovac->hlavnaBudovaUroven_ * KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA);
        if (cas < 0)
        {
            cas = 0; 
        }
        printf("Budova uspesne pridana do radu na zvysovanie. Cas tvania vylepsovania:  %d\n",cas); 
        zvysovac->buffer_[zvysovac->indexVkladania_]->urovenPreCas_++;

        //nastavi cenu dalsieho vylepsenia
        for(int i = 0; i < POCET_DRUHOV_SUROVIN; i++){
        zvysovac->buffer_[zvysovac->indexVyberania_]->cena_[i] += (10 * zvysovac->buffer_[zvysovac->indexVyberania_]->urovenPreCas_);
        }
       
        zvysovac->indexVkladania_ = (zvysovac->indexVkladania_ + 1) % VELKOST_BUFFERA_VYLEPSOVANIA;
        zvysovac->pocetPrvokov_++;
       
        pthread_cond_signal(&zvysovac->producent_);
        pthread_mutex_unlock(&zvysovac->mutex_);
    
    
    
}


void* zvysUrovenObycajnaBudova(void* zvysovacUrovne) {
    zvysovacUrovneBudovaObycajna* zvysovac = zvysovacUrovne;
    
    while (!zvysovac->koniecHry_)
    {
        pthread_mutex_lock(&zvysovac->mutex_);
        while (zvysovac->pocetPrvokov_ == 0 && !zvysovac->koniecHry_ )
        {
            pthread_cond_wait(&zvysovac->producent_, &zvysovac->mutex_);
        }

         if (zvysovac->koniecHry_)
        {
            return NULL;
        }

        
        int cas = (zvysovac->buffer_[zvysovac->indexVyberania_]->uroven_ * KOEFICIENT_ZVYSOVANIE) - 
        (zvysovac->hlavnaBudovaUroven_ * KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA);

         if (cas < 0)
        {
            cas = 0;
        }
       

        pthread_mutex_unlock(&zvysovac->mutex_);
        sleep(cas);
        pthread_mutex_lock(&zvysovac->mutex_);
        
        if (zvysovac->buffer_[zvysovac->indexVyberania_]->typ_ == SKLAD)
        {
            pthread_mutex_lock(zvysovac->mutexVerbovisko_);
            zvysovac->buffer_[zvysovac->indexVyberania_]->pocetZdrojov_ += (zvysovac->buffer_[zvysovac->indexVyberania_]->uroven_ + 1) * KOEFICIENT_KAPACITY_SKLADU;
            pthread_mutex_unlock(zvysovac->mutexVerbovisko_);
        }
        

        zvysovac->buffer_[zvysovac->indexVyberania_]->uroven_++;
        zvysovac->indexVyberania_ = (zvysovac->indexVyberania_ + 1) % VELKOST_BUFFERA_VYLEPSOVANIA;
        zvysovac->pocetPrvokov_--;
        pthread_mutex_unlock(&zvysovac->mutex_);
        
    }
    
    return NULL;

}

void* zvysUrovenArmadnaBudova(void* zvysovacUrovne) {
    zvysovacUrovneBudovaArmada* zvysovac = zvysovacUrovne;
    
    while(!zvysovac->koniecHry_){
        pthread_mutex_lock(&zvysovac->mutex_);
        while (zvysovac->pocetPrvokov_ == 0 && !zvysovac->koniecHry_)
        {
            pthread_cond_wait(&zvysovac->producent_, &zvysovac->mutex_);
        }

         if (zvysovac->koniecHry_)
        {
            return NULL;
        }

        
        int cas = (zvysovac->buffer_[zvysovac->indexVyberania_]->uroven_ * KOEFICIENT_ZVYSOVANIE) - 
        (zvysovac->hlavnaBudovaUroven_ * KOEFICIENT_ZVYSOVANIE_HLAVNA_BUDOVA);

        if (cas < 0)
        {
            cas = 0;
        }
        
        
        pthread_mutex_unlock(&zvysovac->mutex_);
        sleep(cas);
        pthread_mutex_lock(&zvysovac->mutex_);
        

        zvysovac->buffer_[zvysovac->indexVyberania_]->uroven_++;    
        zvysovac->indexVyberania_ = (zvysovac->indexVyberania_ + 1) % VELKOST_BUFFERA_VYLEPSOVANIA;
        zvysovac->pocetPrvokov_--;
        pthread_mutex_unlock(&zvysovac->mutex_);
        
    }
    
    
    return NULL;
   
}








