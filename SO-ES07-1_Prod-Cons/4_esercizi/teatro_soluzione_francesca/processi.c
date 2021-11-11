#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "semafori.h"
#include "processi.h"

void visualizzatore(posto *vet, int id_sem){

	int indice = 0;
	
	while(1){
		
		sleep(1);

		Wait_sem(id_sem, SEMV);

		printf("POSTI DISPONIBILI: %d\n", vet->disp);

		for(int i=0; i<DIM; i++){
	
			printf("N.ro POSTO: %d\n", i);
			if(vet[i].stato == LIBERO){
		
				printf("STATO: %s\n", "LIBERO");

			}else if(vet[i].stato == OCCUPATO){
		
				printf("STATO: %s\n", "OCCUPATO");
			}else
				printf("STATO: %s\n", "IN AGGIORNAMENTO");
		}

		Signal_sem(id_sem, SEMC);

		indice++;
	}
}


void clienti(posto *vet,  int id_sem){

	int s;

	srand(time(NULL));

	s = rand() % 6;
	//sleep(6);
	

	//numero posti da occupare
	int num_posti;
	
	srand(time(NULL));
	num_posti = rand () %4 +1;
	
	Wait_sem(id_sem, SEMC);
	Wait_sem(id_sem, MUTEX);
	if(vet->disp >= num_posti){
	
		vet->disp -= num_posti;

		printf("N.ro dei posti disponibili attualmente: %d\n", vet->disp);


		int i=0;

		while(num_posti != 0){
		
			if(vet[i].stato == LIBERO){
			
				vet[i].stato = IN_AGGIORNAMENTO;

				sleep(1);

				printf("Il cliente %d, ha occupato il posto: %d\n", getpid(), i);

				vet[i].stato = OCCUPATO;

				vet[i].id_cliente = getpid();

				num_posti --;
			}

			i++;
		}
	}else
		printf("NESSUN POSTO DISPONIBILE\n");
		

	Signal_sem(id_sem, SEMV);
	Signal_sem(id_sem, MUTEX);

}
