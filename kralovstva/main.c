
#include "hrac.h"


//dorobit podmienky pre verbovanie a zvysovanie budov...
//konzumer funkcia musi vzdy ist prva!!!!!!!!!!
int main() {
    hrac h;
    
    hracINIT(&h,"/home/janec/semestralnaPraca/kralovstva/pociatocneHodnoty.txt","Jakub");
    hraj(&h);
    
   
   
    //zvysUrovenArmadna(k.budovyObycajne_[HLAVNA_BUDOVA].uroven_,&k.budovyArmady_[0], &k);
   // zvysUrovenArmadnaBudova(&k.zdielanyBufferArmada_);
    //verbuj(&k.budovyArmady_[0], 5, KOPIJNIK);
    //verbuj(&k.budovyArmady_[1], 5, SERMIAR_NA_KONI);
    //pthread_join(vlakno,NULL);
    //vypisInfoKralovstvo(&k);
    //sleep(15);
    //vypisInfoKralovstvo(&k);
    //kralovstvoDestroy(&k);
    //pthread_join(vlakno,NULL);
    return 0;
}


