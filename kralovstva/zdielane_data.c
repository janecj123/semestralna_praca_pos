#include <stdlib.h>
#include <stdio.h>
#include "zdielane_data.h"


/*pri vytvarani funkcii na pracu zo semaformi som sa inspiroval prikladnmi z cviceni*/


void zdielaneDataINIT(zdielaneNazvy* nazvy, zdielaneData* zd){
    
    zd->semMutex_ = sem_open(nazvy->semMutex_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    if (zd->semMutex_ == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    zd->semServerUtoky_ = sem_open(nazvy->semServerUtoky_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    if (zd->semServerUtoky_ == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    zd->semKlientUtoky_ = sem_open(nazvy->semKlientUtoky_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, MAX_POCET_UTOKOV);
    if (zd->semKlientUtoky_ == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    zd->semServerHraci_ = sem_open(nazvy->semServerHraci_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    if (zd->semServerHraci_ == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    zd->semKlientHraci_ = sem_open(nazvy->semKlientHraci_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, MAX_POCET_HRACOV);
    if (zd->semKlientHraci_ == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

 
}



void zdielaneDataDestroy(zdielaneNazvy* nazvy){
    

    if (sem_unlink(nazvy->semMutex_) == -1) {
        perror("Failed to unlink semaphore");
        exit(EXIT_FAILURE);
    }

    
     if (sem_unlink(nazvy->semServerUtoky_) == -1) {
        perror("Failed to unlink semaphore");
        exit(EXIT_FAILURE);
    }

     if (sem_unlink(nazvy->semKlientUtoky_) == -1) {
        perror("Failed to unlink semaphore");
        exit(EXIT_FAILURE);
    }

     if (sem_unlink(nazvy->semServerHraci_) == -1) {
        perror("Failed to unlink semaphore");
        exit(EXIT_FAILURE);
    }

     if (sem_unlink(nazvy->semKlientHraci_) == -1) {
        perror("Failed to unlink semaphore");
        exit(EXIT_FAILURE);
    }


}   



void zdielaneDataOpen(zdielaneData* zd, zdielaneNazvy* nazvy){
    
    shm_buffer_open(nazvy, &zd->buffere_, &zd->fd_);
    
    zd->semMutex_ = sem_open(nazvy->semMutex_, O_RDWR);
    if (zd->semMutex_ == SEM_FAILED) {
        perror("Failed to open semaphore");
        exit(EXIT_FAILURE);
    }
    
    zd->semServerUtoky_ = sem_open(nazvy->semServerUtoky_, O_RDWR);
    if (zd->semServerUtoky_ == SEM_FAILED) {
    perror("Failed to open semaphore");
    exit(EXIT_FAILURE);
    }

    zd->semKlientUtoky_ = sem_open(nazvy->semKlientUtoky_, O_RDWR);
    if (zd->semKlientUtoky_ == SEM_FAILED) {
    perror("Failed to open semaphore");
    exit(EXIT_FAILURE);
    }

    zd->semServerHraci_ = sem_open(nazvy->semServerHraci_, O_RDWR);
    if (zd->semServerHraci_ == SEM_FAILED) {
    perror("Failed to open semaphore");
    exit(EXIT_FAILURE);
    }

    zd->semKlientHraci_ = sem_open(nazvy->semKlientHraci_, O_RDWR);
    if (zd->semKlientHraci_ == SEM_FAILED) {
    perror("Failed to open semaphore");
    exit(EXIT_FAILURE);
    }
   

}



void zdielaneDataClose(zdielaneData* zd){

    shm_buffer_close(zd->fd_, zd->buffere_);
    
    if (sem_close(zd->semMutex_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    } 

    if (sem_close(zd->semServerUtoky_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

    if (sem_close(zd->semKlientUtoky_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

    if (sem_close(zd->semServerHraci_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

    if (sem_close(zd->semKlientHraci_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }


}

void zdielaneDataClose2(zdielaneData* zd){
    if (sem_close(zd->semMutex_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    } 

    if (sem_close(zd->semServerUtoky_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

    if (sem_close(zd->semKlientUtoky_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

    if (sem_close(zd->semServerHraci_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

    if (sem_close(zd->semKlientHraci_) == -1) {
        perror("Failed to close semaphor");
        exit(EXIT_FAILURE);
    }

}


void vlozUtok(zdielaneData* zd, utok* utokPar){
    sem_wait(zd->semKlientUtoky_);
    sem_wait(zd->semMutex_);
    vlozUtokDoBuffera(zd->buffere_, utokPar);
    sem_post(zd->semMutex_);
    sem_post(zd->semServerUtoky_);

}
void vlozHraca(zdielaneData* zd, hracVBufferi* hracPar, hrac* hracVkladany){
    sem_wait(zd->semKlientHraci_);
    sem_wait(zd->semMutex_);
    vlozHracaDoBuffera(zd->buffere_, hracPar, hracVkladany);
    sem_post(zd->semMutex_);
    sem_post(zd->semServerHraci_);

}


void vyberUtok(zdielaneData* zd, utok* utokPar){
    vyberUtokZBuffera(zd->buffere_, utokPar); 
}

int najdiIndexHraca(zdielaneData* zd,char* meno){
    return najdiInexHracaVBuffery(zd->buffere_, meno);
}



void najdiHraca(zdielaneData* zd, bool* bolNajdeny, hracVBufferi* hracHladany, char* meno){
  
    najdiHracaVBuffery(zd->buffere_,bolNajdeny, hracHladany, meno);
    
}

void vyberHraca(zdielaneData* zd, char* meno){
    sem_wait(zd->semServerHraci_);
    sem_wait(zd->semMutex_);
    
    vyberHracaZBuffera(zd->buffere_, meno);
    sem_post(zd->semMutex_);
    sem_post(zd->semKlientHraci_);
}

