#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#include "shm.h"

void shm_init(zdielaneNazvy* nazvy) {
  const int fd_shm = shm_open(nazvy->shm_, O_RDWR | O_CREAT | O_EXCL,
  S_IRUSR | S_IWUSR);
  if (fd_shm == -1) {
    perror("Failed to create shared memory");
    exit(EXIT_FAILURE);
  }
  if (ftruncate(fd_shm, sizeof(zdielaneBuffere)) == -1) {
    perror("Failed to truncate shared memory");
    exit(EXIT_FAILURE);
  }
  zdielaneBuffere *buffere = mmap(NULL, sizeof(zdielaneBuffere), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
  
  zdielaneBuffereINIT(buffere);
  
  shm_buffer_close(fd_shm, buffere);
}

void shm_destroy(zdielaneNazvy* nazvy) {

 
  if (shm_unlink(nazvy->shm_) == -1) {
    perror("Failed to unlink shared memory");
    exit(EXIT_FAILURE);
  }
}

void shm_buffer_open(zdielaneNazvy* nazvy, zdielaneBuffere** zBuffere, int* fd) {
  const int fd_shm = shm_open(nazvy->shm_, O_RDWR, 0);
  if (fd_shm == -1) {
    perror("Failed to open shared memory");
    exit(EXIT_FAILURE);
  }
  zdielaneBuffere *buffere = mmap(NULL, sizeof(zdielaneBuffere), PROT_READ | PROT_WRITE,
  MAP_SHARED, fd_shm, 0);
  if (buffere == MAP_FAILED) {
    perror("Failed to map shared memory");
    exit(EXIT_FAILURE);
  }
  *fd = fd_shm;
  *zBuffere = buffere;
}

void shm_buffer_close(int fd, zdielaneBuffere* zBuffere) {
  if (munmap(zBuffere, sizeof(zdielaneBuffere)) == -1) {
    perror("Failed to unmap shared memory");
    exit(EXIT_FAILURE);
  }
  if (close(fd) == -1) {
    perror("Failed to close shared memory");
    exit(EXIT_FAILURE);
  }
}

