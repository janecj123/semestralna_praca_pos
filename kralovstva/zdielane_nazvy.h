#ifndef ZDIELANE_NAZVY
#define ZDIELANE_NAZVY

typedef struct zidielaneNazvy
{
    char* shm_;
    char* semMutex_;
    char* semServerUtoky_;
    char* semKlientUtoky_;
    char* semServerHraci_;
    char* semKlientHraci_;

}zdielaneNazvy;

void zdielaneNazvyDestroy(zdielaneNazvy* nazvy);
char * add_suffix(const char * name, const char * suffix);
void vytvorNazvy(const char* suffix, zdielaneNazvy* nazvy);
#endif //ZDIELANE_NAZVY