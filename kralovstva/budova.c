#include "budova.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>




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

/*
void* verbovanie (void* verbovac) {
    verbovacArmady* vb = verbovac;
    int cas = 0;
    int zarovnavac = POCET_VOJAKOV_BUDOVA;
    switch (vb->typ_) {
        case KOPIJNIK:
            cas = CAS_VERBOVANIA_KOPIJNIK - vb->budova_->uroven_;
            printf("Verbovanie zacalo. Cas trvania: %d\n", cas);
            sleep(cas);
            vb->budova_->armada_[KOPIJNIK].pocet_ += vb->pocet;
            break;
        case LUKOSTRELEC:
            cas = CAS_VERBOVANIA_LUKOSTRELEC - vb->budova_->uroven_;
            printf("Verbovanie zacalo. Cas trvania: %d\n", cas);
            sleep(cas);
            vb->budova_->armada_[LUKOSTRELEC].pocet_ += vb->pocet;
            break;
        case SERMIAR:
            cas = CAS_VERBOVANIA_SERMIAR - vb->budova_->uroven_;
            printf("Verbovanie zacalo. Cas trvania: %d\n", cas);
            sleep(cas);
            vb->budova_->armada_[SERMIAR].pocet_ += vb->pocet;
            break;
        case LUKOSTRELEC_NA_KONI:
             cas = CAS_VERBOVANIA_LUKOSTRELEC_NA_KONI - vb->budova_->uroven_ * 2;
            printf("Verbovanie zacalo. Cas trvania: %d\n", cas);
            sleep(cas);
            vb->budova_->armada_[LUKOSTRELEC_NA_KONI - zarovnavac].pocet_ += vb->pocet;
            break;
        case SERMIAR_NA_KONI:
            cas = CAS_VERBOVANIA_SERMIAR_NA_KONI - vb->budova_->uroven_ * 2;
            printf("Verbovanie zacalo. Cas trvania: %d\n", cas);
            sleep(cas);
            vb->budova_->armada_[SERMIAR_NA_KONI - zarovnavac].pocet_ += vb->pocet;
            break;
        case KOPIJNIK_NA_KONI:
            cas = CAS_VERBOVANIA_KOPIJNIK_NA_KONI - vb->budova_->uroven_ * 2;
            printf("Verbovanie zacalo. Cas trvania: %d\n", cas);
            sleep(cas);
            vb->budova_->armada_[KOPIJNIK_NA_KONI - zarovnavac].pocet_ += vb->pocet;
            break;
        default:
            break;    
    }

    return NULL;
}
*/
/*
void vylepsiBudovuObycajnu(budovaObycajna* budova, zvysovacUrovneBudovaObycajna* zvysovac){

    zvysovac->budovaNaVylepsenie_ = budova;
    vlozObycajnuBudovuDoBuffera(zvysovac);
};

void vylepsiBudovuArmadnu(budovaArmada* budova, zvysovacUrovneBudovaArmada* zvysovac){
   
    zvysovac->budovaNaVylepsenie_ = budova;
    vlozArmadnuBudovuDoBuffera(zvysovac);
};
*/

//|TODO|
//malo by as dat upravit tak aby tam nebolo potrebne budovaNaVylepsenie_
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
      
        //printf("Zvysovanie urovne zacalo. Cas trvania: %d\n",cas);
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
        
       
        //printf("Zvysovanie urovne budovy zacalo. Cas trvania: %d\n",cas);
        
        pthread_mutex_unlock(&zvysovac->mutex_);
        sleep(cas);
        pthread_mutex_lock(&zvysovac->mutex_);
        zvysovac->buffer_[zvysovac->indexVyberania_]->uroven_++;

        

        zvysovac->indexVyberania_ = (zvysovac->indexVyberania_ + 1) % VELKOST_BUFFERA_VYLEPSOVANIA;
        zvysovac->pocetPrvokov_--;
        //printf("Uroven: %d\n",zvysovac->buffer_[zvysovac->index_]->uroven_);
        pthread_mutex_unlock(&zvysovac->mutex_);
        
    }
    
    
    return NULL;
   
}






//kazdych 5 sekund prida 10 surovin kazdeho druhu
void* spravujSuroviny(void* surovinyPar){
    suroviny* s = surovinyPar;
    time_t casZaciatkuCakania = time(NULL);
    
    while (!s->koniecHry_)
    {
        if (time(NULL) - casZaciatkuCakania <= 5)
        {
            //printf("Rozdiel medzi časmi: %d sekúnd\n", time(NULL) - casZaciatkuCakania );
            sleep(CAS_SPRACOVANIE_SUROVIN - (time(NULL) - casZaciatkuCakania));
            //printf("Spravca surovin zacal pracovat\n");
            pthread_mutex_lock(&s->mutex_);
            s->kamen_ += 10 + s->kamenolom_.uroven_;
            s->drevo_ += 10 + s->drevorubac_.uroven_;
            s->zelezo_ += 10 + s->zeleziarne_.uroven_;
        } else {
            pthread_mutex_lock(&s->mutex_);
            s->kamen_ += 10 + s->kamenolom_.uroven_;
            s->drevo_ += 10 + s->drevorubac_.uroven_;
            s->zelezo_ += 10 + s->zeleziarne_.uroven_;
        }
       
        casZaciatkuCakania = time(NULL);
        pthread_mutex_unlock(&s->mutex_);
    }
     
     return NULL;

}

