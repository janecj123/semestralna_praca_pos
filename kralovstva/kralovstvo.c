#include "kralovstvo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//treba dealokvat vsetky nazvy pomocou nejakej funkcie
void kralovstvoINIT(kralovstvo* kralovstvoPar) {

        budovyObycajneINIT(kralovstvoPar);
        budovyArmadyINIT(kralovstvoPar);
        armadyINIT(kralovstvoPar);


}

void kralovstvoDestroy(kralovstvo* kralovstvoPar){
        free(kralovstvoPar->nazvyObycajnychBudov_);
        free(kralovstvoPar->nazvyArmadnychBudov_);
        free(kralovstvoPar->nazvyVojakov_);
}

char* alokujNazov(char* nazov){
        int dlzka = strlen(nazov);
        char* retazec = calloc(dlzka+1,sizeof(char));
        strcpy(retazec, nazov);
        return retazec;

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

        for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++) {
                kralovstvoPar->budovyObycajne_[i].uroven_ = 0;
                kralovstvoPar->budovyObycajne_[i].pocetZdrojov_ = 0;
                priradMaxUrovenObycajnaBudova(&kralovstvoPar->budovyObycajne_[i]);
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
                priradMaxUrovenArmadnaBudova(&kralovstvoPar->budovyArmady_[i]);
        }

}

void armadyINIT(kralovstvo*  kralovstvoPar) {
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
        kralovstvoPar->budovyArmady_[counter2].armada_[counter++].typ_ = KOPIJNIK;
        kralovstvoPar->budovyArmady_[counter2].armada_[counter++].typ_ = SERMIAR;
        kralovstvoPar->budovyArmady_[counter2].armada_[counter++].typ_ = LUKOSTRELEC;

        counter = 0;
        counter2++;

        kralovstvoPar->budovyArmady_[counter2].armada_[counter++].typ_ = KOPIJNIK_NA_KONI;
        kralovstvoPar->budovyArmady_[counter2].armada_[counter++].typ_ = LUKOSTRELEC_NA_KONI;
        kralovstvoPar->budovyArmady_[counter2].armada_[counter++].typ_ = SERMIAR_NA_KONI;

         for (int j = 0; j < POCET_BUDOV_ARMADA; j++)
         {
                for (int i = 0; i < POCET_VOJAKOV_BUDOVA; i++) {
                        kralovstvoPar->budovyArmady_[j].armada_[i].pocet_ = 0;
                }   
         }
         
        
}


void vypisInfoBudovy(const kralovstvo* kralovstvoPar) {
        for (int i = 0; i < POCET_BUDOV_OBYCAJNA; i++) {
                printf("%s\n",kralovstvoPar->nazvyObycajnychBudov_[i]);
                printf("Uroven: %d\n", kralovstvoPar->budovyObycajne_[i].uroven_);
                printf("Max uroven: %d\n", kralovstvoPar->budovyObycajne_[i].maxUroven_);
                printf("\n");
        }

        for (int i = 0; i < POCET_BUDOV_ARMADA; i++)
        {
                printf("%s\n",kralovstvoPar->nazvyArmadnychBudov_[i]);
                printf("Uroven: %d\n", kralovstvoPar->budovyArmady_[i].uroven_);
                printf("Max uroven: %d\n", kralovstvoPar->budovyArmady_[i].maxUroven_);
                printf("\n");
        }
        
}

void vypisInfoVojsko( const kralovstvo* kralovstvoPar){
        int counter = 0;
        for (int j = 0; j < POCET_BUDOV_ARMADA; j++)
        {
                for (int i = 0; i < POCET_VOJAKOV_BUDOVA; i++)
                {
                        printf("%s: ", kralovstvoPar->nazvyVojakov_[counter++]);
                        printf("%d\n", kralovstvoPar->budovyArmady_[j].armada_[i].pocet_);
                        
                }
        }
        printf("\n");
}
void vypisInfoKralovstvo(const kralovstvo* kralovstvoPar){
        vypisInfoBudovy(kralovstvoPar);
        vypisInfoVojsko(kralovstvoPar);
}