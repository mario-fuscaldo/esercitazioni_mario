#ifndef SEMAFORI_H_
#define SEMAFORI_H_

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int Wait_sem(int id_sem, int numsem);
int Signal_sem(int id_sem, int numsem);



#endif

