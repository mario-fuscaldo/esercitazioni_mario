#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "semafori.h"
#include "processi.h"

int main(){

        key_t k_shm = ftok(PATH, CHAR);

        int id_shm = shmget(k_shm, DIM*sizeof(posto), IPC_CREAT | 0664);

        if(id_shm<0){

                perror("Errore shm\n");
                exit(1);
        }

        posto *vet;

        vet = (posto *) shmat(id_shm, NULL, 0);

        if(vet == (void *)-1){

                perror("Errore shmat\n");
                exit(1);
        }

        key_t k_sem = ftok(PATH,CHAR);

        int id_sem = semget(k_sem, 3, IPC_CREAT | 0664);

        if(id_sem<0){


                perror("Errore sem\n");
                exit(1);
        }

	visualizzatore(vet, id_sem);






	return 0;
}
