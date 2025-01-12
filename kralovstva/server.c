#include "server.h"


void spravujUtoky(zdielaneNazvy* nazvy){
    zdielaneData zd;
    zdielaneDataOpen(&zd,nazvy);
    utok aktualnyUtok;
    bool bolNajdenyUtocnik = false;
    bool bolNajdenyObranca = false;
    hracVBufferi hracVB;
    int indexObranca = 0;
    while(atomic_load(&zd.buffere_->ukonciServer_) == false){
        bolNajdenyUtocnik = false;
        bolNajdenyObranca = false;
      
        sem_wait(zd.semServerUtoky_);
        sem_wait(zd.semMutex_);
        vyberUtok(&zd,&aktualnyUtok);

        najdiHraca(&zd,&bolNajdenyUtocnik,&hracVB,aktualnyUtok.menoUtociaceho_);
        najdiHraca(&zd,&bolNajdenyObranca,&hracVB,aktualnyUtok.menoObrancu_);
        if (bolNajdenyUtocnik && bolNajdenyObranca)
        {
            
        indexObranca = najdiIndexHraca(&zd,aktualnyUtok.menoObrancu_);
        int silaUtoku = vypocitajSiluUtoku(&aktualnyUtok);
        zd.buffere_->bufferHraci_[indexObranca].zmenaVelkosti_ += silaUtoku;   
      
       
        
           
        }

        sem_post(zd.semMutex_);
        sem_post(zd.semKlientUtoky_); 
    
    
    
    }
    zdielaneDataClose(&zd);
}



int vypocitajSiluUtoku(utok* utokPar){
    int sila = 0;
    for (int i = KOPIJNIK_SILA_UTOKU; i < POCET_DRUHOV_VOJAKOV + 1; i++)
    {
        sila += utokPar->poctyVojakov_[i - 1] * i;
    }
    return sila;
}

