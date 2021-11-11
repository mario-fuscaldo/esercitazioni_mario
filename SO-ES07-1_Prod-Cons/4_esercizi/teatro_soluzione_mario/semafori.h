#ifndef SEMAFORI_H_
#define SEMAFORI_H_

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int vado(int id_sem, int numsem);
int vai(int id_sem, int numsem);



#endif

