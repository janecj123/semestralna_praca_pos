
#ifndef SHM
#define SHM

#include "zdielane_nazvy.h"
#include "zdielane_buffere.h"

void shm_init(zdielaneNazvy* nazvy);
void shm_destroy(zdielaneNazvy* nazvy);
void shm_buffer_open(zdielaneNazvy* nazvy, zdielaneBuffere** zBuffere, int* fd);
void shm_buffer_close(int fd, zdielaneBuffere* zBuffere);

#endif // SHM