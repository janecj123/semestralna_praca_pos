
#include "hrac.h"
 

//dorobit podmienky pre verbovanie a zvysovanie budov...
//konzumer funkcia musi vzdy ist prva!!!!!!!!!!
int main() {
    hrac h;
    
    hracINIT(&h,"/home/janec/semestralnaPraca/kralovstva/pociatocneHodnoty.txt","Jakub");
    hraj(&h);
    
    //printf("%d\n",sizeof(pthread_t));
    
   
    
    return 0;
}


