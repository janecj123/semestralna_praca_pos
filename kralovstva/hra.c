
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hra.h"




void hraj(hrac* hracPar){
    

    int volba = 0;
    int pocet = 0;
    
    while (!hracPar->koniecHry_)
    {
        
        hlavneMenu();
        scanf("%d",&volba);
       
        switch (volba)
        {
            case 1:
            
                vypisInformacieMenu();
                scanf("%d",&volba);
                
                switch (volba)
                {
                    case 1:
                        vypisInfoBudovy(hracPar->kralovstvo_);
                        break;
                    case 2:
                        vypisInfoVojsko(hracPar->kralovstvo_);
                        break;
                    case 3:
                        vypisInfoSuroviny(hracPar->kralovstvo_);
                        break;
                    case 4:
                        printf("\n");
                        printf("Kral: %s\n",hracPar->meno_);
                        vypisInfoKralovstvo(hracPar->kralovstvo_);
                        break;
                    case 0:
                        break;;
                    default:
                        break;
                }
                break;

            case 2:
                zvysovanieUrovneMenu();
                scanf("%d",&volba);
               
                switch (volba)
                {
                    case 1:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 2:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[OPEVNENIE],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 3:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[SKLAD],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 4:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[KAMENOLOM],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 5:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[DREVORUBAC],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 6:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[ZELEZIARNE],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 7:
                        zvysUrovenObycajna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyObycajne_[KOSTOL],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferObycajna_);
                        break;
                    case 8:
                        zvysUrovenArmadna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyArmady_[KASARNE ],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferArmada_);
                        break;    
                    case 9:
                        zvysUrovenArmadna(hracPar->kralovstvo_->budovyObycajne_[HLAVNA_BUDOVA].uroven_,&hracPar->kralovstvo_->budovyArmady_[STAJNE],&hracPar->kralovstvo_->suroviny_, &hracPar->kralovstvo_->zdielanyBufferArmada_);
                        break;
                    case 0:
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                verbovanieMenu();
                scanf("%d",&volba);
                if (volba == 0 )
                {
                    break;
                }
                
                printf("Zadajte pocet vojakov: ");
                scanf("%d",&pocet);
                
                switch (volba)
                {
                case 1:
                    verbujNovychVojakov(&hracPar->kralovstvo_->budovyArmady_[KASARNE],pocet,hracPar->kralovstvo_->armada_.vojaci_[volba - 1].typ_,&hracPar->kralovstvo_->suroviny_,&hracPar->kralovstvo_->armada_);
                    break;
                case 2:
                    verbujNovychVojakov(&hracPar->kralovstvo_->budovyArmady_[KASARNE],pocet,hracPar->kralovstvo_->armada_.vojaci_[volba - 1].typ_,&hracPar->kralovstvo_->suroviny_,&hracPar->kralovstvo_->armada_);
                    break;
                case 3:
                    verbujNovychVojakov(&hracPar->kralovstvo_->budovyArmady_[KASARNE],pocet,hracPar->kralovstvo_->armada_.vojaci_[volba - 1].typ_,&hracPar->kralovstvo_->suroviny_,&hracPar->kralovstvo_->armada_);
                    break;
                case 4:
                    verbujNovychVojakov(&hracPar->kralovstvo_->budovyArmady_[STAJNE],pocet,hracPar->kralovstvo_->armada_.vojaci_[volba - 1].typ_,&hracPar->kralovstvo_->suroviny_,&hracPar->kralovstvo_->armada_);
                    break;
                case 5:
                    verbujNovychVojakov(&hracPar->kralovstvo_->budovyArmady_[STAJNE],pocet,hracPar->kralovstvo_->armada_.vojaci_[volba - 1].typ_,&hracPar->kralovstvo_->suroviny_,&hracPar->kralovstvo_->armada_);
                    break;
                case 6:
                    verbujNovychVojakov(&hracPar->kralovstvo_->budovyArmady_[STAJNE],pocet,hracPar->kralovstvo_->armada_.vojaci_[volba - 1].typ_,&hracPar->kralovstvo_->suroviny_,&hracPar->kralovstvo_->armada_);
                    break;
                default:
                    break;
                }
                break;

            case 4:
                pridajUtok(hracPar);
                break;
            case 0:
                ukonciHru(hracPar, hracPar->nazvy_);
               
                return;
            default:
                break;
        }

        

       
    }
   
}

 bool overKoniecHry(hrac* hracPar){
    if(hracPar->koniecHry_){
       return true;
    }
    return false;
}

void zacniHru(hrac* hracPar){
   
    printf("Vitaj %s\n",hracPar->meno_);
    pthread_create(&hracPar->vlakno_,NULL,&aktualizujArmadu,hracPar);
    hraj(hracPar);
    
}



void ukonciHru(hrac* hracPar, zdielaneNazvy nazvy){
    zdielaneData zd;
    atomic_store(&hracPar->koniecHry_,true);
    pthread_join(hracPar->vlakno_,NULL);

    zdielaneDataOpen(&zd,&nazvy);
    vyberHraca(&zd,hracPar->meno_);
    hracDestroy(hracPar);
    printf("Hra bola ukoncena\n");
    
    if (zd.buffere_->pocetPrvkovVHraci_ == 0)
    {
        atomic_store(&zd.buffere_->ukonciServer_,true);
        sem_post(zd.semServerUtoky_);
        
    }
   
    zdielaneDataClose(&zd);
    
    
    
}


void hlavneMenu(){
    
    printf("\n");
    printf("HLAVNE MENU\n");
    printf("1. Vypisat informacie.\n");
    printf("2. Zvysit uroven budovy.\n");
    printf("3. Verbovat vojsko.\n");
    printf("4. Zautoc.\n");
    printf("0. Koniec hry.\n");
    printf("Zadajte volbu: ");
    
}

void vypisInformacieMenu(){
    
    printf("\n");
    printf("VYPISAT INFORMACIE\n");
    printf("1. Vypisat informacie o budovach.\n");
    printf("2. Vypisat informacie o vojsku.\n");
    printf("3. Vypisat informacie o surovinach.\n");
    printf("4. Vypisat informacie o celom kralovstve.\n");
    
    printf("0. Hlavne menu.\n");
    printf("Zadajte volbu: ");

}

void zvysovanieUrovneMenu(){
    
    printf("\n");
    printf("ZVYSOVANIE UROVNE\n");
    printf("1. Zvysit uroven hlavnej budovy.\n");
    printf("2. Zvysit uroven opevnenia.\n");
    printf("3. Zvysit uroven sklad.\n");
    printf("4. Zvysit uroven kamena.\n");
    printf("5. Zvysit uroven drevorubaca.\n");
    printf("6. Zvysit uroven zeleziarne.\n");
    printf("7. Zvysit uroven kostol.\n");
    printf("8. Zvysit uroven kasarne.\n");
    printf("9. Zvysit uroven stajne.\n");

    printf("0. Hlavne menu.\n");
    printf("Zadajte volbu: ");
}
void verbovanieMenu(){
    
    printf("\n");
    printf("VERBOVANIE VOJSKA\n");
    printf("1. Verbovat kopijnikov.\n");
    printf("2. Verbovat sermiarov.\n");
    printf("3. Verbovat lukostrelcov.\n");
    printf("4. Verbovat kopijnikov na koni.\n");
    printf("5. Verbovat lukostrelcov na koni.\n");
    printf("6. Verbovat sermiarov na koni.\n");
   

    printf("0. Hlavne menu.\n");
    printf("Zadajte volbu: ");
}



void pridajUtok(hrac* utocnik){
    char meno[50];
    int pocet = 0;
    int volba = 0;
    bool bolNajdeny = false;
    utok novyUtok;
    zdielaneData zd;
    hracVBufferi obranca;

    zdielaneDataOpen(&zd,&utocnik->nazvy_);

    sem_wait(zd.semMutex_);

    //kontrola ci neni plny buffer utokov
    if (zd.buffere_->pocetPrvkovVUtoky_ == MAX_POCET_UTOKOV)
    {
        printf("Rada utokov je plna. Skuste pridat utok znovu trochu neskor.\n");
        sem_post(zd.semMutex_);
        zdielaneDataClose(&zd);
        return;
    }
   
    printf("Zadajte meno hraca: ");
    scanf("%s",meno);
    
    //kontroluje ci hrac s danym menom existuje 
    while(!bolNajdeny){
         
         if (strcmp(meno,utocnik->meno_) == 0)
        {
            printf("Nemozete utocit sam na seba\n");
            bolNajdeny = false;
             printf("Zadajte meno hraca znovu: ");
            scanf("%s",meno);
            continue;
        }
        
        najdiHraca(&zd,&bolNajdeny,&obranca,meno);
        
        if (!bolNajdeny)
        {
            printf("\n");
            printf("Hrac s menom %s neexistuje.\n",meno);
            printf("1.Zadat nove meno obrancu.\n");
            printf("0.Ukoncit utok.\n");
            printf("Zadajte volbu: ");
            scanf("%d",&volba);
            if (volba == 1)
            {
                printf("Zadajte meno hraca: ");
                scanf("%s",meno);
            }
            else
            {
                sem_post(zd.semMutex_);
                return;
            }
        }
       
       
        
    }
    
    
    strcpy(novyUtok.menoObrancu_,meno);
    strcpy(novyUtok.menoUtociaceho_,utocnik->meno_);
    novyUtok.velkostArmady_ = 0;
    
    pthread_mutex_lock(&utocnik->kralovstvo_->armada_.mutex_);
    
    //pridanie vojakov do utoku
    for (int i = 0; i < POCET_DRUHOV_VOJAKOV; i++)
    {
        printf("Zadajte pocet jednotiek %s (aktualny stav %d): ",utocnik->kralovstvo_->nazvyVojakov_[i],utocnik->kralovstvo_->armada_.vojaci_[i].pocet_);
        scanf("%d",&pocet);
        while (pocet > utocnik->kralovstvo_->armada_.vojaci_[i].pocet_)
        {
            printf("Nesdostatok vojakov. Zadaj pocet znovu: \n");
             scanf("%d",&pocet);
        }
        
        novyUtok.poctyVojakov_[i] = pocet;
        novyUtok.velkostArmady_ += pocet;
        utocnik->kralovstvo_->armada_.vojaci_[i].pocet_ -= pocet;
        utocnik->kralovstvo_->armada_.velkostArmady_ -= pocet;
    }

    if (novyUtok.velkostArmady_ == 0)
    {
        printf("\n");
        printf("Nemozete utocit s prazdnou armadou\n");
        pthread_mutex_unlock(&utocnik->kralovstvo_->armada_.mutex_);
        sem_post(zd.semMutex_);
        zdielaneDataClose(&zd);
        return;
    }
    

    sem_post(zd.semMutex_);
    vlozUtok(&zd,&novyUtok);
    
    pthread_mutex_unlock(&utocnik->kralovstvo_->armada_.mutex_);
    
    zdielaneDataClose(&zd);
}


//funkica kazdu sekundu aktualizuje informacie o utokoch na hraca zo servera. Nasledne tieto utoky vyhodnoti.
void* aktualizujArmadu(void* arg){
    hrac* aktualnyHrac = arg;
    hracVBufferi hracVB;
    zdielaneData zd;
    bool bolNajdeny = false;
    int index = 0;
    
    zdielaneDataOpen(&zd,&aktualnyHrac->nazvy_); 
    while (atomic_load(&aktualnyHrac->koniecHry_) == false)
    {
        sem_wait(zd.semMutex_);
        pthread_mutex_lock(&aktualnyHrac->kralovstvo_->armada_.mutex_);
        najdiHraca(&zd,&bolNajdeny,&hracVB,aktualnyHrac->meno_);

        //ak hrac bol zniceny ukonci jeho hru a vypise informaciu
        if (hracVB.zmenaVelkosti_ > aktualnyHrac->kralovstvo_->armada_.velkostArmady_ + aktualnyHrac->kralovstvo_->budovyObycajne_[OPEVNENIE].uroven_ * 2)
        {
            printf("\n");
            printf("Bol si zniceny. Pre ukoncenie programu stlac tlacidlo 0.\n");
            atomic_store(&aktualnyHrac->koniecHry_,true);
            atomic_store(&aktualnyHrac->prehra_,true);
            sem_post(zd.semMutex_);
            pthread_mutex_unlock(&aktualnyHrac->kralovstvo_->armada_.mutex_);
            break;
        }
        

        index = najdiIndexHraca(&zd,aktualnyHrac->meno_);
        zd.buffere_->bufferHraci_[index].zmenaVelkosti_ = 0;
        sem_post(zd.semMutex_);

        if(hracVB.zmenaVelkosti_> aktualnyHrac->kralovstvo_->budovyObycajne_[OPEVNENIE].uroven_ * 2){
            hracVB.zmenaVelkosti_ -= aktualnyHrac->kralovstvo_->budovyObycajne_[OPEVNENIE].uroven_ * 2;
        for (int i = KOPIJNIK_SILA_UTOKU; i < POCET_DRUHOV_VOJAKOV + 1; i++)
        {
            
        if(aktualnyHrac->kralovstvo_->armada_.vojaci_[i-1].pocet_ * i < hracVB.zmenaVelkosti_){
            hracVB.zmenaVelkosti_ -= aktualnyHrac->kralovstvo_->armada_.vojaci_[i-1].pocet_ * i;
            aktualnyHrac->kralovstvo_->armada_.vojaci_[i-1].pocet_ = 0;
        } else {
            aktualnyHrac->kralovstvo_->armada_.vojaci_[i-1].pocet_ -= hracVB.zmenaVelkosti_ / i;
            break;
        }
        }
        }

        pthread_mutex_unlock(&aktualnyHrac->kralovstvo_->armada_.mutex_);
        sleep(1);
    }

    zdielaneDataClose(&zd);
    
    return NULL;


}



void hraINIT(hrac* hracPar,zdielaneNazvy* nazvy, char* meno, char* cesta, hracVBufferi* hracVB){
    zdielaneData zd;
    hracINIT(hracPar,cesta,meno,nazvy);
    pridajHraca(&zd,nazvy,hracPar,hracVB);
}

void pridajHraca(zdielaneData* zd, zdielaneNazvy* nazvy, hrac* hracPar, hracVBufferi* hracVB){
    
    zdielaneDataOpen(zd,nazvy);
    vlozHraca(zd,hracVB ,hracPar);
    zdielaneDataClose(zd);
    
}

