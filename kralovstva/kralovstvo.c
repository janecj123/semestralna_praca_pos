#include "kralovstvo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//treba dealokvat vsetky nazvy pomocou nejakej funkcie
void kralovstvoINIT(kralovstvo* kralovstvoPar, char* cesta, pthread_t* vlaknoSuroviny, pthread_t* vlaknoPridavanieObycajnychBudov, pthread_t* vlaknoPridavanieArmadnychBudov, pthread_t* vlaknoArmady) {

        budovyObycajneINIT(kralovstvoPar);
        budovyArmadyINIT(kralovstvoPar);
        vojaciINIT(kralovstvoPar);
        armadaINIT(&kralovstvoPar->armada_);
        pociatoceHodnotyINIT(kralovstvoPar, cesta);
        zvysovacUrovneObycajnaINIT(kralovstvoPar->budovyObycajne_[HLAVNA_BUDOVA].uroven_, &kralovstvoPar->zdielanyBufferObycajna_);
        zvysovacUrovneArmadnaINIT(kralovstvoPar->budovyObycajne_[HLAVNA_BUDOVA].uroven_, &kralovstvoPar->zdielanyBufferArmada_ );
       
        pthread_mutex_init(&kralovstvoPar->suroviny_.mutex_, NULL);
        pthread_mutex_init(&kralovstvoPar->mutex_, NULL);
        
        //spustenie manazera surovin
        pthread_mutex_lock(&kralovstvoPar->suroviny_.mutex_);
        pthread_create(vlaknoSuroviny,NULL,&spravujSuroviny, &kralovstvoPar->suroviny_);
        pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);

        pthread_mutex_lock(&kralovstvoPar->zdielanyBufferObycajna_.mutex_);
        pthread_create(vlaknoPridavanieObycajnychBudov,NULL,&zvysUrovenObycajnaBudova, &kralovstvoPar->zdielanyBufferObycajna_);
        pthread_mutex_unlock(&kralovstvoPar->zdielanyBufferObycajna_.mutex_);
        
        pthread_mutex_lock(&kralovstvoPar->zdielanyBufferArmada_.mutex_);
        pthread_create(vlaknoPridavanieArmadnychBudov,NULL,&zvysUrovenArmadnaBudova, &kralovstvoPar->zdielanyBufferArmada_);
        pthread_mutex_unlock(&kralovstvoPar->zdielanyBufferArmada_.mutex_);

        pthread_mutex_lock(&kralovstvoPar->armada_.mutex_);
        pthread_create(vlaknoArmady,NULL,&verbuj, &kralovstvoPar->armada_);
        pthread_mutex_unlock(&kralovstvoPar->armada_.mutex_);
}



void budovyObycajneINIT(kralovstvo* kralovstvoPar) {
        
        int counter = 0;
        kralovstvoPar->nazvyObycajnychBudov_ = calloc(POCET_BUDOV_OBYCAJNA, sizeof(char*));

        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Hlavna budova";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Opevnenie";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Kostol";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Kamenolom";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Drevorubac";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Zeleziarne";
        kralovstvoPar->nazvyObycajnychBudov_[counter++] = "Verbovisko";

        counter = 0;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = HLAVNA_BUDOVA;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = OPEVNENIE;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = KOSTOL;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = KAMENOLOM;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = DREVORUBAC;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = ZELEZIARNE;
        kralovstvoPar->budovyObycajne_[counter++].typ_ = VERBOVISKO;

         for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++) 
        {
                kralovstvoPar->budovyObycajne_[i].uroven_ = 0;
                kralovstvoPar->budovyObycajne_[i].urovenPreCas_ = 0;
                priradMaxUrovenObycajnaBudova(&kralovstvoPar->budovyObycajne_[i]);
                kralovstvoPar->budovyObycajne_[i].pocetZdrojov_= 0; 
                kralovstvoPar->budovyObycajne_[i].jeVBufferi_ = false;      
        }

        kralovstvoPar->suroviny_.kamenolom_ = kralovstvoPar->budovyObycajne_[KAMENOLOM];
        kralovstvoPar->suroviny_.drevorubac_ = kralovstvoPar->budovyObycajne_[DREVORUBAC];
        kralovstvoPar->suroviny_.zeleziarne_ = kralovstvoPar->budovyObycajne_[ZELEZIARNE];
       
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
                kralovstvoPar->budovyArmady_[i].jeVBufferi_ = false;
        }
       
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
       

        for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++)
        {
                for (int j = 0; j < POCET_DRUHOV_SUROVIN; j++)
                {
                        fscanf(subor, "%d", &pocet);
                        kralovstvoPar->budovyObycajne_[i].cena_[j] = pocet;
                }  
        }

        fscanf(subor, "%s", nazov);
       

         for (int i = 0; i < POCET_BUDOV_ARMADA; i++)
        {
                for (int j = 0; j < POCET_DRUHOV_SUROVIN; j++)
                {
                        fscanf(subor, "%d", &pocet);
                        kralovstvoPar->budovyArmady_[i].cena_[j] = pocet;
                        
                }  
        } 

         fscanf(subor, "%s", nazov);

        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                for (int j = 0; j < POCET_DRUHOV_SUROVIN; j++)
                {
                        fscanf(subor, "%d", &pocet);
                        kralovstvoPar->armada_.vojaci_[i].cena_[j] = pocet;     
                        
                }
                
        }
        
        fscanf(subor, "%s", nazov);

        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                fscanf(subor, "%d", &pocet);
                kralovstvoPar->armada_.vojaci_[i].casVerbovania_ = pocet;
                printf("cas verbovania: %d\n",kralovstvoPar->armada_.vojaci_[i].casVerbovania_);
        }

        fclose(subor);

}



void zvysovacUrovneObycajnaINIT(int hlavnaBudovaUroven, zvysovacUrovneBudovaObycajna* zvysovac) {

        zvysovac->hlavnaBudovaUroven_ = hlavnaBudovaUroven;
        zvysovac->buffer_ = calloc(VELKOST_BUFFERA_VYLEPSOVANIA, sizeof(budovaObycajna));
        zvysovac->koniecHry_ = false;
        zvysovac->pocetPrvokov_ = 0;
        zvysovac->indexVkladania_ = 0;
        zvysovac->indexVyberania_ = 0;

        pthread_cond_init(&zvysovac->producent_, NULL);
        pthread_cond_init(&zvysovac->konzument_, NULL);
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
        pthread_cond_init(&zvysovac->konzument_, NULL);
        pthread_mutex_init(&zvysovac->mutex_, NULL);

}

void kralovstvoDestroy(kralovstvo* kralovstvoPar,  pthread_t vlaknoSuroviny, pthread_t vlaknoPridavanieObycajnychBudov, pthread_t vlaknoPridavanieArmadnychBudov, pthread_t vlaknoArmady) {
        
        pthread_cancel(vlaknoSuroviny);
        pthread_cancel(vlaknoPridavanieArmadnychBudov);
        pthread_cancel(vlaknoPridavanieObycajnychBudov);
        pthread_cancel(vlaknoArmady);
        pthread_join(vlaknoArmady,NULL);
        pthread_join(vlaknoPridavanieObycajnychBudov,NULL);
        pthread_join(vlaknoPridavanieArmadnychBudov,NULL); 
        pthread_join(vlaknoSuroviny,NULL);

        armadaDestroy(&kralovstvoPar->armada_);
        zvysovacUrovneObycajnaDestroy(&kralovstvoPar->zdielanyBufferObycajna_);
        zvysovacUronveArmadnaDestroy(&kralovstvoPar->zdielanyBufferArmada_);
        

        pthread_mutex_destroy(&kralovstvoPar->mutex_);
        pthread_mutex_destroy(&kralovstvoPar->suroviny_.mutex_);
        

        free(kralovstvoPar->nazvyObycajnychBudov_);
        free(kralovstvoPar->nazvyArmadnychBudov_);
        free(kralovstvoPar->nazvyVojakov_);

        
}




void zvysovacUrovneObycajnaDestroy(zvysovacUrovneBudovaObycajna* zvysovac){
        
       // zvysovac->koniecHry_ = true;
        //pthread_cond_signal(&zvysovac->producent_);
       // sleep(1);
        free(zvysovac->buffer_);
        pthread_cond_destroy(&zvysovac->producent_);
        pthread_cond_destroy(&zvysovac->konzument_);
        pthread_mutex_destroy(&zvysovac->mutex_);
}
void zvysovacUronveArmadnaDestroy(zvysovacUrovneBudovaArmada* zvysovac){
        
        //zvysovac->koniecHry_ = true;
        //pthread_cond_signal(&zvysovac->producent_);
        //sleep(1);
        free(zvysovac->buffer_);
        pthread_cond_destroy(&zvysovac->producent_);
        pthread_cond_destroy(&zvysovac->konzument_);
        pthread_mutex_destroy(&zvysovac->mutex_);
}



//|TODO| zemnit aby parameter nebolo kralovstov ale iba suroviny
void zvysUrovenObycajna(int hlavnaBudovaUroven, budovaObycajna* budovaNaVylepsenie, kralovstvo* kralovstvoPar){
        
        pthread_mutex_lock(&kralovstvoPar->suroviny_.mutex_);
        if (overDostatokSurovinAUrovenObycajna(kralovstvoPar,budovaNaVylepsenie) && daSaPridatObycajna(&kralovstvoPar->zdielanyBufferObycajna_))
        {
                //odpocita cenu vylepsenia zo zdrojov surovin 
                int counter = 0;
                kralovstvoPar->suroviny_.kamen_ -= budovaNaVylepsenie->cena_[counter++];
                kralovstvoPar->suroviny_.drevo_ -= budovaNaVylepsenie->cena_[counter++];
                kralovstvoPar->suroviny_.zelezo_ -= budovaNaVylepsenie->cena_[counter++];
                pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);

               
                kralovstvoPar->zdielanyBufferObycajna_.hlavnaBudovaUroven_ = hlavnaBudovaUroven;
                vlozObycajnuBudovuDoBuffera(&kralovstvoPar->zdielanyBufferObycajna_, budovaNaVylepsenie);   
        } else {
                pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);
        }     
       
}

//|TODO| zemnit aby parameter nebolo kralovstov ale iba suroviny
void zvysUrovenArmadna(int hlavnaBudovaUroven, budovaArmada* budovaNaVylepsenie, kralovstvo* kralovstvoPar){
        
        pthread_mutex_lock(&kralovstvoPar->suroviny_.mutex_);
        if (overDostatokSurovinAUrovenArmadna(kralovstvoPar,budovaNaVylepsenie) && daSaPridatArmadna(&kralovstvoPar->zdielanyBufferArmada_)){
               
                //odpocita cenu vylepsenia zo zdrojov surovin 
                int counter = 0;
                kralovstvoPar->suroviny_.kamen_ -= budovaNaVylepsenie->cena_[counter++];
                kralovstvoPar->suroviny_.drevo_ -= budovaNaVylepsenie->cena_[counter++];
                kralovstvoPar->suroviny_.zelezo_ -= budovaNaVylepsenie->cena_[counter++];
                pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);

                //kralovstvoPar->zdielanyBufferArmada_.budovaNaVylepsenie_ = budovaNaVylepsenie;
                kralovstvoPar->zdielanyBufferArmada_.hlavnaBudovaUroven_ = hlavnaBudovaUroven;
                vlozArmadnuBudovuDoBuffera(&kralovstvoPar->zdielanyBufferArmada_, budovaNaVylepsenie);
        } else {
                 pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);
        }
}

bool daSaPridatObycajna(zvysovacUrovneBudovaObycajna* zvysovac){

        
        if (zvysovac->pocetPrvokov_  == VELKOST_BUFFERA_VYLEPSOVANIA)
        {
                pthread_mutex_unlock(&zvysovac->mutex_);
                printf("Rad na vylepsenie je plny! Pockaj kym sa uvolni miesto.\n");
                return false;
        }


        
        return true;
}
bool daSaPridatArmadna(zvysovacUrovneBudovaArmada* zvysovac){

        
        if (zvysovac->pocetPrvokov_  == VELKOST_BUFFERA_VYLEPSOVANIA)
        {
                pthread_mutex_unlock(&zvysovac->mutex_);
                printf("Rad na vylepsenie je plny! Pockaj kym sa uvolni miesto.\n");
                return false;
        }
      
       
        return true;
}

bool overDostatokSurovinAUrovenObycajna(kralovstvo* kralovstvoPar, budovaObycajna* budova){
        
        
         if (budova->urovenPreCas_ == budova->maxUroven_)
        {
                printf("Budova je na maximalnej uroveni!!\n");
                return false;
        }
        
        int counter = 0;

        if (kralovstvoPar->suroviny_.kamen_ < budova->cena_[counter++])
        {
                printf("Nedostatok kamena!\n");
                return false;
        } else if (kralovstvoPar->suroviny_.drevo_ < budova->cena_[counter++])
        {
                printf("Nedostatok dreva!\n");
                return false;
        } else if (kralovstvoPar->suroviny_.zelezo_ < budova->cena_[counter++])
        {
                printf("Nedostatok zeleza!\n");
                return false;
        }
        return true;

}

bool overDostatokSurovinAUrovenArmadna(kralovstvo* kralovstvoPar, budovaArmada* budova){
       
       
         if (budova->urovenPreCas_ == budova->maxUroven_)
        {
                printf("Budova je na maximalnej uroveni!!\n");
        }

        int counter = 0;
       
        if (kralovstvoPar->suroviny_.kamen_ < budova->cena_[counter++])
        {
                printf("Nedostatok kamena!\n");
                return false;
        } else if (kralovstvoPar->suroviny_.drevo_ < budova->cena_[counter++])
        {
                printf("Nedostatok dreva!\n");
                return false;
        } else if (kralovstvoPar->suroviny_.zelezo_ < budova->cena_[counter++])
        {
                printf("Nedostatok zeleza!\n");
                return false;
        }
        return true;
       
        

}

void verbujNovychVojakov(budovaArmada* budova,int pocet, typVojaka typ ,suroviny* surovinyPar, armada* armadaPar){       

        pthread_mutex_lock(&surovinyPar->mutex_);
        if (overDostatokSurovinNaVerbovanie(surovinyPar, armadaPar, typ, pocet) && daSaPridatVerbovanie(armadaPar, budova, typ))
        {
                
                int counter = 0;
                surovinyPar->kamen_ -= armadaPar->vojaci_[typ].cena_[counter++] * pocet;
                surovinyPar->drevo_ -= armadaPar->vojaci_[typ].cena_[counter++] * pocet;
                surovinyPar->zelezo_ -= armadaPar->vojaci_[typ].cena_[counter++] * pocet;

                pthread_mutex_unlock(&surovinyPar->mutex_);
                vlozPrikazNaVerbovanieDoBuffera(budova, typ, pocet, armadaPar);
                
        }else{
        pthread_mutex_unlock(&surovinyPar->mutex_);
        }

}

bool daSaPridatVerbovanie(armada* armadaPar, budovaArmada* budova, typVojaka typ){
        
        pthread_mutex_lock(&armadaPar->mutex_);
        if (armadaPar->pocetPrvokov_ == VELKOST_BUFFERA_VERBOVANIA)
        {
                printf("Rad na verbovanie je plny! Pockaj kym sa uvolni miesto.\n");
                pthread_mutex_unlock(&armadaPar->mutex_);
                return false;
        }
        pthread_mutex_unlock(&armadaPar->mutex_);

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


/*
void verbuj(budovaArmada* budova,int pocet ,typVojaka typ){
        
        verbovacArmady verbovac = {budova,pocet,typ};

        if (typ == KOPIJNIK && budova->typ_ == KASARNE)
        {
                verbovanie(&verbovac);      
        } else if (typ == SERMIAR && budova->typ_ == KASARNE)
        {
                verbovanie(&verbovac);      
        } else if (typ == LUKOSTRELEC && budova->typ_ == KASARNE)
        {
                verbovanie(&verbovac);      
        } else if (typ == KOPIJNIK_NA_KONI && budova->typ_ == STAJNE)
        {
                verbovanie(&verbovac);      
        } else if (typ == LUKOSTRELEC_NA_KONI && budova->typ_ == STAJNE)
        {
                verbovanie(&verbovac);      
        } else if (typ == SERMIAR_NA_KONI && budova->typ_ == STAJNE)
        {
                verbovanie(&verbovac);
        } else
        {
                printf("Zvoleneho vojaka nie je mozne verbovat v tejto budove!\n");
        }
        
        
}
*/



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
        
        int counter = 0;
        printf("\n");
        for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
        {
                
                printf("%s: ", kralovstvoPar->nazvyVojakov_[i]);
                printf("%d\n", kralovstvoPar->armada_.vojaci_[i].pocet_);
                        
                
        }
        printf("\n");
}

void vypisInfoSuroviny( kralovstvo* kralovstvoPar){
        
        pthread_mutex_lock(&kralovstvoPar->suroviny_.mutex_);
        printf("\n");
        printf("Kamen: %d\n", kralovstvoPar->suroviny_.kamen_);
        printf("Drevo: %d\n", kralovstvoPar->suroviny_.drevo_);
        printf("Zelezo: %d\n", kralovstvoPar->suroviny_.zelezo_);
        printf("\n");
        pthread_mutex_unlock(&kralovstvoPar->suroviny_.mutex_);
}

void vypisInfoKralovstvo(kralovstvo* kralovstvoPar){
        vypisInfoBudovy(kralovstvoPar);
        vypisInfoSuroviny(kralovstvoPar);
        vypisInfoVojsko(kralovstvoPar);
}