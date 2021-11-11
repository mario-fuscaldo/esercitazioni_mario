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

	for(int i=0; i<DIM; i++){
	
		vet[i].id_cliente = 0;
		vet[i].stato = LIBERO;
		vet[i].disp = DIM;
	}

	key_t k_sem = ftok(PATH,CHAR);

	int id_sem = semget(k_sem, 3, IPC_CREAT | 0664);

	if(id_sem<0){
	
	
		perror("Errore sem\n");
		exit(1);
	}

	semctl(id_sem, MUTEX, SETVAL, 1);
	semctl(id_sem, SEMC, SETVAL, 1);
	semctl(id_sem,SEMV,SETVAL, 1);

	int pid;

	for(int i=0; i<CLIENTI; i++){
	
		pid=fork();

		if(pid==0){
		
			printf("Sono il CLIENTE\n");
			clienti(vet, id_sem);
			exit(0);
		}
	}

	for(int i=0; i<VISUALIZZATORE; i++){
	
		pid=fork();

		if(pid == 0){
		
			execl("./visualizzatore", "", (char *)0);
		}
	}


	for(int i=0; i<CLIENTI+VISUALIZZATORE; i++){
	
		wait(NULL);
	}

	semctl(id_sem, 0, IPC_RMID);
	shmctl(id_shm, IPC_RMID, NULL);



	return 0;
}
