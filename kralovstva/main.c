
#include "server.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {
    hrac h;
    int volba = 0;
    zdielaneNazvy nazvy;
    hracVBufferi hracVB;
    char meno[50];
    bool bolNajdeny = false;
    

    printf("Vytaj v hre Suboj kralovstiev.\n");
    printf("1.Vytvorit server.\n");
    printf("2.Pripojit sa na server.\n");
    printf("3.Ukoncit hru.\n");
    printf("Zadajte volbu: ");
    scanf("%d",&volba);
    zdielaneData zd;
    switch (volba)
    {
    case 1:
        printf("Zadajte meno servera: ");
        scanf("%s",meno);
        vytvorNazvy(meno,&nazvy);
        shm_init(&nazvy);
        zdielaneDataINIT(&nazvy,&zd);
        printf("Server vytvoreny\n");
        spravujUtoky(&nazvy);
        sleep(1);
        
        zdielaneDataClose2(&zd);
        shm_destroy(&nazvy); 
        zdielaneDataDestroy(&nazvy);
        printf("Nazov: %s\n",nazvy.shm_);
        zdielaneNazvyDestroy(&nazvy);
        
        break;
    
       
    case 2:
        printf("Zadajte meno servera: ");
        scanf("%s",meno);
        vytvorNazvy(meno,&nazvy);
        printf("Zadajte svoje meno v hre: ");
        zdielaneDataOpen(&zd,&nazvy);
        while(!bolNajdeny){
        scanf("%s",meno);
        najdiHraca(&zd,&bolNajdeny,&hracVB,meno);
        if (!bolNajdeny)
        {
            break;
        }else{
            printf("Taketo meno sa uz nachadza na tomto servery. Zadajte nove meno: ");
        }
        }
        zdielaneDataClose(&zd);
        hraINIT(&h,&nazvy,meno,"/home/janec/semestralnaPraca/subojKralovstiev/pociatocneHodnoty.txt",&hracVB);
        zacniHru(&h);
        
        zdielaneNazvyDestroy(&nazvy);
        break;
    case 3:
    
        printf("Zadajte meno servera: ");
        scanf("%s",meno);
        vytvorNazvy(meno,&nazvy);
        shm_destroy(&nazvy);
        zdielaneDataDestroy(&nazvy);
        zdielaneNazvyDestroy(&nazvy);
        printf("Dovidenia\n");
    
        return 0;
        
    default:
        printf("Zla volba!!!!!!\n");
        break;
    }    

    return 0;
}


