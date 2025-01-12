
#ifndef ZDIELANE_DATA
#define ZDIELANE_DATA

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "shm.h"





typedef struct zdielaneData
{
    zdielaneBuffere* buffere_;
    int fd_;
    sem_t* semMutex_;
    sem_t* semServerUtoky_;
    sem_t* semKlientUtoky_;
    sem_t* semServerHraci_;
    sem_t* semKlientHraci_;
   
    
}zdielaneData;



void zdielaneDataINIT(zdielaneNazvy* nazvy, zdielaneData* zd);
void zdielaneDataDestroy(zdielaneNazvy* nazvy);
void zdielaneDataOpen(zdielaneData* zd, zdielaneNazvy* nazvy);
void zdielaneDataClose(zdielaneData* zd);
void zdielaneDataClose2(zdielaneData* zd);
void vlozUtok(zdielaneData* zd, utok* utokPar);
void vlozHraca(zdielaneData* zd, hracVBufferi* hracPar, hrac* hracVkladany);
void vyberUtok(zdielaneData* zd, utok* utokPar);
int najdiIndexHraca(zdielaneData* zd,char* meno);
void najdiHraca(zdielaneData* zd, bool* bolNajdeny, hracVBufferi* hracHladany, char* meno);
void vyberHraca(zdielaneData* zd, char* meno);


#endif //ZDIELANE_DATA