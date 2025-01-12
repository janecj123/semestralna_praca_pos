
#include "zdielane_nazvy.h"
#include <string.h>
#include <stdlib.h>


void zdielaneNazvyDestroy(zdielaneNazvy* nazvy){
    free(nazvy->shm_);
    free(nazvy->semMutex_);
    free(nazvy->semServerUtoky_);
    free(nazvy->semKlientUtoky_);
    free(nazvy->semServerHraci_);
    free(nazvy->semKlientHraci_);
}

//funkcia prebrata z cviceni 
char * add_suffix(const char* name, const char* suffix){
  const int name_len = strlen(name);
  const int new_len = name_len + strlen(suffix) + 2;
  char * result = calloc(new_len, sizeof(char));
  strcpy(result, name);
  result[name_len] = '-';
  strcpy(result + name_len + 1, suffix);
  return result;
}

void vytvorNazvy(const char* suffix, zdielaneNazvy* nazvy){
    nazvy->shm_ = add_suffix("SHM", suffix);
    nazvy->semMutex_ = add_suffix("SEM-MUTEX", suffix);
    nazvy->semServerUtoky_ = add_suffix("SEM-SERVER_UTOKY", suffix);
    nazvy->semKlientUtoky_ = add_suffix("SEM-KLIENT_UTOKY", suffix);
    nazvy->semServerHraci_ = add_suffix("SEM-SERVER-HRACI", suffix);
    nazvy->semKlientHraci_ = add_suffix("SEM-KLIENT-HRACI", suffix);
    
}
