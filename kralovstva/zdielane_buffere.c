
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zdielane_buffere.h"

void zdielaneBuffereINIT(zdielaneBuffere* buffere){
   
    buffere->pocetPrvkovVHraci_ = 0;
    buffere->pocetPrvkovVUtoky_ = 0;
    buffere->indexVkladaniaHraci_ = 0;
    buffere->indexVkladaniaUtoky_ = 0;
    buffere->indexVyberaniaUtoky_ = 0;
    buffere->ukonciServer_ = ATOMIC_VAR_INIT(false);
   
}




void vlozHracaDoBuffera(zdielaneBuffere* buffere, hracVBufferi* hracPar, hrac* hracVkladany){
    
    hracPar->zmenaVelkosti_ = 0;
    strncpy(hracPar->meno_,hracVkladany->meno_,MAX_DLZKA_MENA - 1);
    hracPar->meno_[MAX_DLZKA_MENA - 1] = '\0';
    buffere->bufferHraci_[buffere->indexVkladaniaHraci_] = *hracPar;
    buffere->indexVkladaniaHraci_ = (buffere->indexVkladaniaHraci_ + 1) % MAX_POCET_HRACOV;
    buffere->pocetPrvkovVHraci_++;
    
}





void vlozUtokDoBuffera(zdielaneBuffere* buffere, utok* utokPar){
   
    buffere->bufferUtoky_[buffere->indexVkladaniaUtoky_] = *utokPar;
    buffere->indexVkladaniaUtoky_ = (buffere->indexVkladaniaUtoky_ + 1) % MAX_POCET_UTOKOV;
    buffere->pocetPrvkovVUtoky_++;
 
    
}


void vyberHracaZBuffera(zdielaneBuffere* buffere, char* meno){
    int poradie = 0;
  
    for (int i = 0; i < buffere->pocetPrvkovVHraci_; i++)
    {
       
        if (strcmp(buffere->bufferHraci_[i].meno_,meno) == 0)
        {
        
            
            poradie = i;
            break;
        }
    }

    

   
    for (int i = poradie; i < buffere->pocetPrvkovVHraci_ - 1; i++)
    {
       buffere->bufferHraci_[i] = buffere->bufferHraci_[i+1];

       
    }
    buffere->indexVkladaniaHraci_--;
    buffere->pocetPrvkovVHraci_--;
      
}





void vyberUtokZBuffera(zdielaneBuffere* buffere, utok* utokPar){
    
    *utokPar = buffere->bufferUtoky_[buffere->indexVyberaniaUtoky_];
    buffere->indexVyberaniaUtoky_ = (buffere->indexVyberaniaUtoky_ + 1) % MAX_POCET_UTOKOV;
    buffere->pocetPrvkovVUtoky_--;


}
 

void najdiHracaVBuffery(zdielaneBuffere* buffere, bool* bolNajdeny, hracVBufferi* hracHladany, char* meno){
    
    for (int i = 0; i < buffere->pocetPrvkovVHraci_; i++)
    {
        
        if (strcmp(buffere->bufferHraci_[i].meno_,meno) == 0)
        {
            *hracHladany = buffere->bufferHraci_[i];
            *bolNajdeny = true;
            return;
           
        }
    }
    
}


int najdiInexHracaVBuffery(zdielaneBuffere* buffere, char* meno){
    for (int i = 0; i < buffere->pocetPrvkovVHraci_; i++)
    {
        if (strcmp(buffere->bufferHraci_[i].meno_,meno) == 0)
        {
            return i;
        }
    }
    return -1;
}