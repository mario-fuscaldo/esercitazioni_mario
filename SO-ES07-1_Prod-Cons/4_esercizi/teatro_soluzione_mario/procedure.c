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
#include "procedure.h"


void visualizzatore(posto* p, int sem_id){

    while(1){

        sleep(1);

		Signal_Sem(sem_id, MUTEX);

		for(int i=0; i<MAX_POSTI; i++){

		printf("N.ro POSTO: %d ;", i);

		if(p[i].stato == LIBERO){

			printf("STATO: %s\n", "LIBERO");

		}else if(p[i].stato == OCCUPATO){
			printf("STATO: %s\n", "OCCUPATO");
			printf(" DA: %d\n", p[i].id_cliente);

		}else
			printf("STATO: %s\n", "IN AGGIORNAMENTO");
		}

		Wait_Sem(sem_id, MUTEX);
    }	
}

void cliente(posto* p, int sem_id, int* posti_disp){
    
    //tempo di attesa(0-5s);
	int s;
	srand(time(NULL));
	s = rand() % 6;
	
	
	//numero posti da occupare(1-4)
	int num_posti;
	srand(time(NULL));
	num_posti = rand () %4 +1;
	

	//controllo posti disponibili e decremento

	if(*posti_disp >= num_posti){
		Wait_Sem(sem_id, SEM_NUM_POSTI);

		*posti_disp -= num_posti;

		Signal_Sem(sem_id, SEM_NUM_POSTI);


	//accesso a sezione critica
		Wait_Sem(sem_id, MUTEX);
		int i=0;
		while(num_posti != 0){

			if(p[i].stato == LIBERO){
				p[i].stato = IN_AGGIORNAMENTO;
				sleep(1);
				//printf("Il cliente %d, ha occupato il posto: %d\n", getpid(), i);
				p[i].stato = OCCUPATO;
				p[i].id_cliente = getpid();
				num_posti --;
			}else
				i++;
		}
	}else
		printf("NON ABBASTANZA POSTI DISPONIBI\n");

		Signal_Sem(sem_id, MUTEX);
}