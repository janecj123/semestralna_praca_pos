#include "kralovstvo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void kralovstvoINIT(kralovstvo* kralovstvoPar, char* cesta) {

        pthread_mutex_init(&kralovstvoPar->mutexKralovstvo_, NULL);
        pthread_mutex_init(&kralovstvoPar->mutexVerbovisko_, NULL);
        pthread_mutex_init(&kralovstvoPar->suroviny_.mutex_, NULL);

        budovyObycajneINIT(kralovstvoPar);
        budovyArmadyINIT(kralovstvoPar);
        surovinyINIT(kralovstvoPar);
        vojaciINIT(kralovstvoPar);
        armadaINIT(&kralovstvoPar->armada_);
        zvysovacUrovneObycajnaINIT(kralovstvoPar->budovyObycajne_[HLAVNA_BUDOVA].uroven_, &kralovstvoPar->zdielanyBufferObycajna_, &kralovstvoPar->mutexVerbovisko_);
        zvysovacUrovneArmadnaINIT(kralovstvoPar->budovyObycajne_[HLAVNA_BUDOVA].uroven_, &kralovstvoPar->zdielanyBufferArmada_ );
        pociatoceHodnotyINIT(kralovstvoPar, cesta);

        
        
        
        //spustenie manazera surovin
        pthread_mutex_lock(&kralovstvoPar->suroviny_.mutex_);
        pthread_create(&kralovstvoPar->vlaknoSuroviny_,NULL,&spravujSuroviny, &kralovstvoPar->suroviny_);
        pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);

        pthread_mutex_lock(&kralovstvoPar->zdielanyBufferObycajna_.mutex_);
        pthread_create(&kralovstvoPar->vlaknoPridavanieObycajnychBudov_,NULL,&zvysUrovenObycajnaBudova, &kralovstvoPar->zdielanyBufferObycajna_);
        pthread_mutex_unlock(&kralovstvoPar->zdielanyBufferObycajna_.mutex_);
        
        pthread_mutex_lock(&kralovstvoPar->zdielanyBufferArmada_.mutex_);
        pthread_create(&kralovstvoPar->vlaknoPridavanieArmadnychBudov_,NULL,&zvysUrovenArmadnaBudova, &kralovstvoPar->zdielanyBufferArmada_);
        pthread_mutex_unlock(&kralovstvoPar->zdielanyBufferArmada_.mutex_);

        pthread_mutex_lock(&kralovstvoPar->armada_.mutex_);
        pthread_create(&kralovstvoPar->vlaknoArmady_,NULL,&verbuj, &kralovstvoPar->armada_);
        pthread_mutex_unlock(&kralovstvoPar->armada_.mutex_);
}

void kralovstvoDestroy(kralovstvo* kralovstvoPar) {
        
        pthread_cancel(kralovstvoPar->vlaknoSuroviny_);
        pthread_cancel(kralovstvoPar->vlaknoPridavanieArmadnychBudov_);
        pthread_cancel(kralovstvoPar->vlaknoPridavanieObycajnychBudov_);
  
        pthread_cancel(kralovstvoPar->vlaknoArmady_);
      
        pthread_join(kralovstvoPar->vlaknoArmady_,NULL);
        pthread_join(kralovstvoPar->vlaknoPridavanieObycajnychBudov_,NULL);
        pthread_join(kralovstvoPar->vlaknoPridavanieArmadnychBudov_,NULL); 
        pthread_join(kralovstvoPar->vlaknoSuroviny_,NULL);

        armadaDestroy(&kralovstvoPar->armada_);
        zvysovacUrovneObycajnaDestroy(&kralovstvoPar->zdielanyBufferObycajna_);
        zvysovacUronveArmadnaDestroy(&kralovstvoPar->zdielanyBufferArmada_);
        

        pthread_mutex_destroy(&kralovstvoPar->suroviny_.mutex_);
        pthread_mutex_destroy(&kralovstvoPar->mutexVerbovisko_);
        pthread_mutex_destroy(&kralovstvoPar->mutexKralovstvo_);
       
        

       
        free(kralovstvoPar->nazvyObycajnychBudov_);
        free(kralovstvoPar->nazvyArmadnychBudov_);
        free(kralovstvoPar->nazvyVojakov_);
        
        
}


void budovyObycajneINIT(kralovstvo* kralovstvoPar) {
        
        int counter = 0;
        kralovstvoPar->nazvyObycajnychBudov_ = calloc(POCET_BUDOV_OBYCAJNA, sizeof(char*));

        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Hlavna budova";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Opevnenie";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Sklad";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Kamenolom";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Drevorubac";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Zeleziarne";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Verbovisko";

        counter = 0;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = HLAVNA_BUDOVA;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = OPEVNENIE;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = SKLAD;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = KAMENOLOM;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = DREVORUBAC;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = ZELEZIARNE;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = KOSTOL;

         for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++) 
        {
                kralovstvoPar->budovyObycajne_[i].uroven_ = 0;
                kralovstvoPar->budovyObycajne_[i].urovenPreCas_ = 0;
                priradMaxUrovenObycajnaBudova(&kralovstvoPar->budovyObycajne_[i]);
                kralovstvoPar->budovyObycajne_[i].pocetZdrojov_= 0;     
        }

        
       
}

void budovyArmadyINIT(kralovstvo* kralovstvoPar) {
         
        int counter = 0;
        kralovstvoPar->nazvyArmadnychBudov_ = calloc(POCET_BUDOV_ARMADA, sizeof(char*));

       
        kralovstvoPar->nazvyArmadnychBudov_[counter++] = "Kasarne";
        kralovstvoPar->nazvyArmadnychBudov_[counter++] = "Stajne";

        counter = 0;
        kralovstvoPar->budovyArmady_[counter++].typ_ = KASARNE;
        kralovstvoPar->budovyArmady_[counter++].typ_ = STAJNE;


        
        for (int i = 0; i < POCET_BUDOV_ARMADA; i++) {
                kralovstvoPar->budovyArmady_[i].uroven_ = 0;
                kralovstvoPar->budovyArmady_[i].urovenPreCas_ = 0;
                priradMaxUrovenArmadnaBudova(&kralovstvoPar->budovyArmady_[i]);
        }
       
}

void surovinyINIT(kralovstvo* kralovstvoPar){

        kralovstvoPar->suroviny_.kamenolom_ = &kralovstvoPar->budovyObycajne_[KAMENOLOM];
        kralovstvoPar->suroviny_.drevorubac_ = &kralovstvoPar->budovyObycajne_[DREVORUBAC];
        kralovstvoPar->suroviny_.zeleziarne_ = &kralovstvoPar->budovyObycajne_[ZELEZIARNE];
        kralovstvoPar->suroviny_.sklad_ = &kralovstvoPar->budovyObycajne_[SKLAD];
        kralovstvoPar->suroviny_.mutexVerbovisko_ = &kralovstvoPar->mutexVerbovisko_;
        
        
}

void vojaciINIT(kralovstvo*  kralovstvoPar) {
        int counter = 0;
        int counter2 = 0;

        kralovstvoPar->nazvyVojakov_ = calloc(POCET_DRUHOV_VOJAKOV, sizeof(char*));

        kralovstvoPar->nazvyVojakov_[counter++] = "Kopijnik";
        kralovstvoPar->nazvyVojakov_[counter++] = "Sermiar";
        kralovstvoPar->nazvyVojakov_[counter++] = "Lukostrelec";
        kralovstvoPar->nazvyVojakov_[counter++] = "Kopijnik na koni";
        kralovstvoPar->nazvyVojakov_[counter++] = "Lukostrelec na koni";
        kralovstvoPar->nazvyVojakov_[counter++] = "Sermiar na koni";

        counter = 0;
        kralovstvoPar->budovyArmady_[counter2].typVojaka_[counter++] = KOPIJNIK;
        kralovstvoPar->budovyArmady_[counter2].typVojaka_[counter++] = SERMIAR;
        kralovstvoPar->budovyArmady_[counter2].typVojaka_[counter++] = LUKOSTRELEC;

        counter = 0;
        counter2++;

        kralovstvoPar->budovyArmady_[counter2].typVojaka_[counter++] = KOPIJNIK_NA_KONI;
        kralovstvoPar->budovyArmady_[counter2].typVojaka_[counter++] = LUKOSTRELEC_NA_KONI;
        kralovstvoPar->budovyArmady_[counter2].typVojaka_[counter++] = SERMIAR_NA_KONI;


         
        
}

void pociatoceHodnotyINIT(kralovstvo* kralovstvoPar, char* cesta){
        
        FILE*  subor = fopen(cesta,"r");
        if (subor == NULL) {
        fprintf(stderr, "Subor sa nepodarilo otvorit:  %s\n",cesta);
        return;
        }

        int pocet = 0;

        //inicializacia surovim
        kralovstvoPar->suroviny_.koniecHry_ = false;
        fscanf(subor, "%d", &pocet);
        kralovstvoPar->suroviny_.kamen_ = pocet;
        fscanf(subor, "%d", &pocet);
        kralovstvoPar->suroviny_.drevo_ = pocet;
        fscanf(subor, "%d", &pocet);
        kralovstvoPar->suroviny_.zelezo_ = pocet;

        char nazov[50];
        fscanf(subor, "%s", nazov);
       
        //inicializacia ceny budov obycajnych
        for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++)
        {
                for (int j = 0; j < POCET_DRUHOV_SUROVIN; j++)
                {
                        fscanf(subor, "%d", &pocet);
                        kralovstvoPar->budovyObycajne_[i].cena_[j] = pocet;
                }  
        }

        fscanf(subor, "%s", nazov);
       
        //inicializacia ceny budov armadnych
         for (int i = 0; i < POCET_BUDOV_ARMADA; i++)
        {
                for (int j = 0; j < POCET_DRUHOV_SUROVIN; j++)
                {
                        fscanf(subor, "%d", &pocet);
                        kralovstvoPar->budovyArmady_[i].cena_[j] = pocet;
                        
                }  
        } 

        fscanf(subor, "%s", nazov);

        //inicializacia ceny verbovania vojakov
        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                for (int j = 0; j < POCET_DRUHOV_SUROVIN; j++)
                {
                        fscanf(subor, "%d", &pocet);
                        kralovstvoPar->armada_.vojaci_[i].cena_[j] = pocet;     
                        
                }
                
        }
        
        fscanf(subor, "%s", nazov);

        //inicializacia casu verbovania vojakov
        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                fscanf(subor, "%d", &pocet);
                kralovstvoPar->armada_.vojaci_[i].casVerbovania_ = pocet;
                printf("cas verbovania: %d\n",kralovstvoPar->armada_.vojaci_[i].casVerbovania_);
        }

        fscanf(subor, "%s", nazov);

        //inicializacia pociatocnej velkosti skladu
        fscanf(subor, "%d", &pocet);
        kralovstvoPar->budovyObycajne_[SKLAD].pocetZdrojov_ = pocet;


        fclose(subor);

}









void zvysUrovenObycajna(int hlavnaBudovaUroven, budovaObycajna* budovaNaVylepsenie, suroviny* surovinyPar, zvysovacUrovneBudovaObycajna* zvysovac){   
        
        pthread_mutex_lock(&surovinyPar->mutex_);
        if (overDostatokSurovinAUrovenObycajna(surovinyPar,budovaNaVylepsenie) && daSaPridatObycajna(zvysovac))
        {
                //odpocita cenu vylepsenia zo zdrojov surovin 
                int counter = 0;
                surovinyPar->kamen_ -= budovaNaVylepsenie->cena_[counter++];
                surovinyPar->drevo_ -= budovaNaVylepsenie->cena_[counter++];
                surovinyPar->zelezo_ -= budovaNaVylepsenie->cena_[counter++];
                pthread_mutex_unlock(&surovinyPar->mutex_);

               
                zvysovac->hlavnaBudovaUroven_ = hlavnaBudovaUroven;
                vlozObycajnuBudovuDoBuffera(zvysovac, budovaNaVylepsenie);   
        } else {
                pthread_mutex_unlock(&surovinyPar->mutex_);
        }     
       
}


void zvysUrovenArmadna(int hlavnaBudovaUroven, budovaArmada* budovaNaVylepsenie, suroviny* surovinyPar, zvysovacUrovneBudovaArmada* zvysovac){
        
        pthread_mutex_lock(&surovinyPar->mutex_);
        if (overDostatokSurovinAUrovenArmadna(surovinyPar,budovaNaVylepsenie) && daSaPridatArmadna(zvysovac)){
               
                //odpocita cenu vylepsenia zo zdrojov surovin 
                int counter = 0;
                surovinyPar->kamen_ -= budovaNaVylepsenie->cena_[counter++];
                surovinyPar->drevo_ -= budovaNaVylepsenie->cena_[counter++];
                surovinyPar->zelezo_ -= budovaNaVylepsenie->cena_[counter++];
                pthread_mutex_unlock(&surovinyPar->mutex_);

                
                zvysovac->hlavnaBudovaUroven_ = hlavnaBudovaUroven;
                vlozArmadnuBudovuDoBuffera(zvysovac, budovaNaVylepsenie);
        } else {
                 pthread_mutex_unlock(&surovinyPar->mutex_);
        }
}

bool daSaPridatObycajna(zvysovacUrovneBudovaObycajna* zvysovac){

        pthread_mutex_lock(&zvysovac->mutex_);
        if (zvysovac->pocetPrvokov_  == VELKOST_BUFFERA_VYLEPSOVANIA)
        {
                pthread_mutex_unlock(&zvysovac->mutex_);
                printf("Rad na vylepsenie je plny! Pockaj kym sa uvolni miesto.\n");
                return false;
        }
        pthread_mutex_unlock(&zvysovac->mutex_);

        
        return true;
}
bool daSaPridatArmadna(zvysovacUrovneBudovaArmada* zvysovac){

        pthread_mutex_lock(&zvysovac->mutex_);
        if (zvysovac->pocetPrvokov_  == VELKOST_BUFFERA_VYLEPSOVANIA)
        {
                pthread_mutex_unlock(&zvysovac->mutex_);
                printf("Rad na vylepsenie je plny! Pockaj kym sa uvolni miesto.\n");
                return false;
        }
        pthread_mutex_unlock(&zvysovac->mutex_);
       
        return true;
}

bool overDostatokSurovinAUrovenObycajna(suroviny* surovinyPar, budovaObycajna* budova){
        
        
         if (budova->urovenPreCas_ == budova->maxUroven_)
        {
                printf("Budova je na maximalnej uroveni!!\n");
                return false;
        }
        
        int counter = 0;

        if (surovinyPar->kamen_ < budova->cena_[counter++])
        {
                printf("Nedostatok kamena! Na vylepsenie potrebuješ %d kamena.\n", budova->cena_[counter-1]);
                return false;
        } else if (surovinyPar->drevo_ < budova->cena_[counter++])
        {
                printf("Nedostatok dreva! Na vylepsenie potrebuješ %d dreva.\n", budova->cena_[counter-1]);
                return false;
        } else if (surovinyPar->zelezo_ < budova->cena_[counter++])
        {
                printf("Nedostatok zeleza! Na vylepsenie potrebuješ %d zeleza.\n", budova->cena_[counter-1]);
                return false;
        }
        return true;

}

bool overDostatokSurovinAUrovenArmadna(suroviny* surovinyPar, budovaArmada* budova){
       
       
         if (budova->urovenPreCas_ == budova->maxUroven_)
        {
                printf("Budova je na maximalnej uroveni!!\n");
        }

        int counter = 0;
       
        if (surovinyPar->kamen_ < budova->cena_[counter++])
        {
                printf("Nedostatok kamena! Na vylepsenie potrebuješ %d kamena.\n", budova->cena_[counter-1]);
                return false;
        } else if (surovinyPar->drevo_ < budova->cena_[counter++])
        {
                printf("Nedostatok dreva! Na vylepsenie potrebuješ %d dreva.\n", budova->cena_[counter-1]);
                return false;
        } else if (surovinyPar->zelezo_ < budova->cena_[counter++])
        {
                printf("Nedostatok zeleza! Na vylepsenie potrebuješ %d zeleza.\n", budova->cena_[counter-1]);
                return false;
        }
        return true;
       
        

}

void verbujNovychVojakov(budovaArmada* budova,int pocet, typVojaka typ ,suroviny* surovinyPar, armada* armadaPar){       

        pthread_mutex_lock(&surovinyPar->mutex_);
        if (overDostatokSurovinNaVerbovanie(surovinyPar, armadaPar, typ, pocet) && daSaPridatVerbovanie(armadaPar, budova, typ, pocet))
        {
                
                int counter = 0;
                surovinyPar->kamen_ -= armadaPar->vojaci_[typ].cena_[counter++] * pocet;
                surovinyPar->drevo_ -= armadaPar->vojaci_[typ].cena_[counter++] * pocet;
                surovinyPar->zelezo_ -= armadaPar->vojaci_[typ].cena_[counter++] * pocet;

                pthread_mutex_unlock(&surovinyPar->mutex_);
                
                armadaPar->velkostArmady_ += pocet;
                vlozPrikazNaVerbovanieDoBuffera(budova, typ, pocet, armadaPar);
                
        }else{
        pthread_mutex_unlock(&surovinyPar->mutex_);
        }

}

bool daSaPridatVerbovanie(armada* armadaPar, budovaArmada* budova, typVojaka typ, int pocet){
        
        
        if (armadaPar->pocetPrvokov_ == VELKOST_BUFFERA_VERBOVANIA)
        {
                printf("Rad na verbovanie je plny! Pockaj kym sa uvolni miesto.\n");
                pthread_mutex_unlock(&armadaPar->mutex_);
                return false;
        }
        

        if (armadaPar->velkostArmady_ + pocet > MAX_POCET_VOJAKOV)
        {
                printf("Nie je mozne verbovat dalsich vojakov. Maximalny pocet vojakov je %d!\n",MAX_POCET_VOJAKOV);
                return false;
        }
        

        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                if (budova->typVojaka_[i] == typ)
                {
                        return true;
                } 
                
        }
        
        printf("V tejto budove nie je mozne verbovat tento typ vojaka!");
        return false;
}

bool overDostatokSurovinNaVerbovanie(suroviny* surovinyPar, armada* armadaPar, typVojaka typ, int pocet){

        int counter = 0;

        
        if (surovinyPar->kamen_ < armadaPar->vojaci_[typ].cena_[counter++] * pocet)
        {
                printf("Nedostatok kamena!\n");
                return false;
        } else if (surovinyPar->drevo_ < armadaPar->vojaci_[typ].cena_[counter++] * pocet)
        {
                printf("Nedostatok dreva!\n");
                return false;
        } else if (surovinyPar->zelezo_ < armadaPar->vojaci_[typ].cena_[counter++] * pocet)
        {
                printf("Nedostatok zeleza!\n");
                return false;
        }
        return true;
}


//kazde 2 sekundy prida surovin kazdeho druhu ak je volne miesto v sklade
void* spravujSuroviny(void* surovinyPar){
    suroviny* s = surovinyPar;
    time_t casZaciatkuCakania = time(NULL);
    
    while (!s->koniecHry_)
    {

        if (time(NULL) - casZaciatkuCakania <= CAS_SPRACOVANIE_SUROVIN)
        {
            
                sleep(CAS_SPRACOVANIE_SUROVIN - (time(NULL) - casZaciatkuCakania));
              
                pthread_mutex_lock(&s->mutex_);
                pthread_mutex_lock(s->mutexVerbovisko_);
                //overuje ci je dostatok miesta v sklade
                if (s->kamen_ >= s->sklad_->pocetZdrojov_)
                {
                    s->kamen_ = s->sklad_->pocetZdrojov_;
                }else{
                   s->kamen_ += POCET_PRIDANYCH_SUROVIN + s->kamenolom_->uroven_;
                }
            
                if (s->drevo_ >= s->sklad_->pocetZdrojov_)
                {
                        s->drevo_ = s->sklad_->pocetZdrojov_;
                }else{
                        s->drevo_ += POCET_PRIDANYCH_SUROVIN + s->drevorubac_->uroven_;
                }
            
                if (s->zelezo_ >= s->sklad_->pocetZdrojov_)
                {
                        s->zelezo_ = s->sklad_->pocetZdrojov_;      
                } else {
                        s->zelezo_ += POCET_PRIDANYCH_SUROVIN + s->zeleziarne_->uroven_;
                }
                
            
        } else {
            pthread_mutex_lock(&s->mutex_);
            pthread_mutex_lock(s->mutexVerbovisko_);
            //overuje ci je dostatok miesta v sklade
            if (s->kamen_ >= s->sklad_->pocetZdrojov_)
                {
                    s->kamen_ = s->sklad_->pocetZdrojov_;
                }else{
                   s->kamen_ += POCET_PRIDANYCH_SUROVIN + s->kamenolom_->uroven_;
                }
            
                if (s->drevo_ >= s->sklad_->pocetZdrojov_)
                {
                        s->drevo_ = s->sklad_->pocetZdrojov_;
                }else{
                        s->drevo_ += POCET_PRIDANYCH_SUROVIN + s->drevorubac_->uroven_;
                }
            
                if (s->zelezo_ >= s->sklad_->pocetZdrojov_)
                {
                        s->zelezo_ = s->sklad_->pocetZdrojov_;      
                } else {
                        s->zelezo_ += POCET_PRIDANYCH_SUROVIN + s->zeleziarne_->uroven_;
                }
        }
       
        casZaciatkuCakania = time(NULL);
        pthread_mutex_unlock(s->mutexVerbovisko_);
        pthread_mutex_unlock(&s->mutex_);
    }
     
     return NULL;

}



void vypisInfoBudovy( kralovstvo* kralovstvoPar) {
         
       pthread_mutex_lock(&kralovstvoPar->zdielanyBufferObycajna_.mutex_);
        printf("\n");
        for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++) {
                printf("%s\n",kralovstvoPar->nazvyObycajnychBudov_[i]);
                printf("Uroven: %d\n", kralovstvoPar->budovyObycajne_[i].uroven_);
                printf("Max uroven: %d\n", kralovstvoPar->budovyObycajne_[i].maxUroven_);
                
        }
        pthread_mutex_unlock(&kralovstvoPar->zdielanyBufferObycajna_.mutex_);

        pthread_mutex_lock(&kralovstvoPar->zdielanyBufferArmada_.mutex_);
        for (int i = 0; i < POCET_BUDOV_ARMADA; i++)
        {
                printf("%s\n",kralovstvoPar->nazvyArmadnychBudov_[i]);
                printf("Uroven: %d\n", kralovstvoPar->budovyArmady_[i].uroven_);
                printf("Max uroven: %d\n", kralovstvoPar->budovyArmady_[i].maxUroven_);
                
        }
        printf("\n");
        pthread_mutex_unlock(&kralovstvoPar->zdielanyBufferArmada_.mutex_);
        
}


void vypisInfoVojsko( kralovstvo* kralovstvoPar){
        
        pthread_mutex_lock(&kralovstvoPar->armada_.mutex_);
        printf("\n");
        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                
                printf("%s: ", kralovstvoPar->nazvyVojakov_[i]);
                printf("%d\n", kralovstvoPar->armada_.vojaci_[i].pocet_);
                        
                
        }
        printf("\n");
        pthread_mutex_unlock(&kralovstvoPar->armada_.mutex_);
}

void vypisInfoSuroviny( kralovstvo* kralovstvoPar){
        
        pthread_mutex_lock(&kralovstvoPar->suroviny_.mutex_);
        printf("\n");
        printf("Kamen: %d\n", kralovstvoPar->suroviny_.kamen_);
        printf("Drevo: %d\n", kralovstvoPar->suroviny_.drevo_);
        printf("Zelezo: %d\n", kralovstvoPar->suroviny_.zelezo_);
        printf("Kapacita skladu: %d\n", kralovstvoPar->suroviny_.sklad_->pocetZdrojov_);
        printf("\n");
        pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);
}

void vypisInfoKralovstvo(kralovstvo* kralovstvoPar){

        vypisInfoBudovy(kralovstvoPar);
        vypisInfoSuroviny(kralovstvoPar);
        vypisInfoVojsko(kralovstvoPar);
}