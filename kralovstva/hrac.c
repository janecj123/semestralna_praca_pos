#include "hrac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void hracINIT(hrac* hracPar, char* cesta, char* meno) {

    kralovstvo* k = malloc(sizeof(kralovstvo));
    
    hracPar->kralovstvo_ = k;
    hracPar->meno_ = calloc(strlen(meno)+1,sizeof(char));
    strcpy(hracPar->meno_, meno);
    kralovstvoINIT(hracPar->kralovstvo_, cesta); 

}

void hracDestroy(hrac* hracPar){

    kralovstvoDestroy(hracPar->kralovstvo_);
    free(hracPar->meno_);
    free(hracPar->kralovstvo_);
    
}

void zacniHru(hrac* hracPar){
    hraj(hracPar);
}

void hraj(hrac* hracPar){
    

    int volba = 0;
    int pocet = 0;
    
    while (1)
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
                        vypisInfoKralovstvo(hracPar->kralovstvo_);
                        break;
                    case 0:
                        break;;
                    default:
                        break;
                }
                break;
            //dorobit aby zobrazovvalo cenu vylepsenia
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
                if (volba == 0)
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
                //zautoc(hracPar);
                break;   
            case 0:
                ukonciHru(hracPar);
                return;
            default:
                break;
        }

        

       
    }
}

void ukonciHru(hrac* hracPar){
    hracDestroy(hracPar);
}


void prehra(hrac* hracPar){
    printf("Prehral si\n");
    ukonciHru(hracPar);

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