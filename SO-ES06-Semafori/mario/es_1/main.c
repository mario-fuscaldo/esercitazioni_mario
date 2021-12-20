/*  
*   In questo esercizio, si implementa una comunicazione inter-processo utilizzando una shared memory, disciplinando l'accesso con un semaforo.
*   In particolare, si vuole creare 2 processi figli che incrementano per 100 volte una variable intera memorizzata nella shared memory.
*  
*   
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "semafori.h"

int main(){


    //chiavi private perché non devono comunicare con altri processi
    //chiave shared memory
    key_t chiaveshm = IPC_PRIVATE;
    //chiave semafori
    key_t chiavesem = IPC_PRIVATE;
    
    //ottengo sharedmemory
    id_t idshm= shmget (chiaveshm, sizeof(int), IPC_CREAT|0664);
    if(idshm<0){
        perror("ERRORE SHM");
        exit(1);
    }



    //ottengo semafori
    id_t idsem= semget (chiavesem, 1 ,IPC_CREAT|0664) ;
    if(idsem<0){
        perror("ERRORE SEM");
        exit(1);
    }


    //attacco la shm
    int * ptr= shmat(idshm, 0, 0);
	if(ptr  == (void *)-1) {
		perror("Errore SHMAT");
		exit(1);
	}

    //inizializzo semaforo 0 a 1 (quindi è quello che va avanti)
    semctl(idsem, 0, SETVAL, 1);

    //inizio a mettere valore nella shm
    *ptr = 0;
	printf("VALORE INIZIALE: %d\n", *ptr);

    //fork e esecuzione

    for(int i=0;i<2;i++){
        
        pid_t pid = fork();

		if(pid < 0) {
			perror("Errore FORK");
			exit(1);
		}

        // processo figlio
        if(pid==0){

            //operazioni
            for(int j=0; j<100; j++){

                //entra area protetta
                Wait_Sem(idsem,0);

                
               //operazione
               *ptr=*ptr+1;
                printf("Processo %d, con pid %d ha incrementato\n", i, pid);
                printf("valore incrementato = %d h\n", *ptr);


               Signal_Sem(idsem,0);
            }
            exit(0);
        }
    }

    //aspetto i figli

    for(int i=0; i<2;i++)
        wait(NULL);


    //dealloco shm e sem

    shmctl(idshm, IPC_RMID,0);
    semctl(idsem, IPC_RMID,0);
    return 0;    
}