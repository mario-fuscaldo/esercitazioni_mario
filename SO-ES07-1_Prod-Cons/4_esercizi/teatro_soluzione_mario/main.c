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
#include "procedure.h"

int main(){

    //shared memory
    key_t chiave = IPC_PRIVATE;

    int DIM_BUFFER =DIM*sizeof(posto);

	int id_shm = shmget(chiave, DIM_BUFFER, IPC_CREAT|0664);

	if(id_shm<0) { perror("SHM errore"); exit(1); }

    posto *p;

    p = (posto *) shmat(id_shm, NULL, 0); 

        if(p == (void *)-1){

            perror("Errore shmat\n");
            exit(1);
        }


    //semafori
    key_t chiavesem = IPC_PRIVATE;

	int ds_sem = semget(chiavesem, 1, IPC_CREAT|0664);

	if(ds_sem<0) { perror("SEM errore"); exit(1); }



    //settaggio mutex
    semctl(ds_sem, ENTRO_IO, SETVAL, 1);


    for(int i=0; i<CLIENTI; i++) {

		int pid = fork();

		if(pid==0) {


            presaDelPosto(p, ds_sem);

			exit(1);
		}
	}


    int pid = fork();
    if (pid==0){
    visualizzazione(p);
    exit(1);
    }

    for(int i=0; i<CLIENTI; i++) {
    wait(NULL);
    printf("cliente terminato\n");
	}
    wait(NULL);
    printf("visualizzatore terminato\n");

    shmctl(id_shm, IPC_RMID, NULL);
    semctl(ds_sem, 0, IPC_RMID);

    return 0;
}