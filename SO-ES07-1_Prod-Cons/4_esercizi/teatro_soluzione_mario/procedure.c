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


void visualizzazione(posto p [DIM]){

    while(1){

        sleep(1);

		for(int i=0; i<DIM; i++){

		printf("N.ro POSTO: %d ;", i);

		if(p[i].stato == LIBERO){

			printf("STATO: %s\n", "LIBERO");

		}else if(p[i].stato == OCCUPATO){
			printf("STATO: %s\n", "OCCUPATO");
			printf("OCCUPATO DA: %d\n", p[i].id_cliente);

		}else
			printf("STATO: %s\n", "IN AGGIORNAMENTO");
		}
    }	
}

void presaDelPosto(posto p [DIM],  int id_sem){
    
    //tempo di attesa(0-5s);
	int s;
	srand(time(NULL));
	s = rand() % 6;
	
	
	//numero posti da occupare(1-4)
	int num_posti;
	srand(time(NULL));
	num_posti = rand () %4 +1;
	
	//serve un modo per trovare la disponibilità 
	//così è una barabrie ma non ho altri metodi
    int disp = DIM;
	for(int i=0; i<DIM; i++){
		if (p[i].stato!=LIBERO)
			disp--;

	}
	
	if(disp >= num_posti){
	//entra nella sezione critica
	vado(id_sem, ENTRO_IO);
		disp -= num_posti;

		
		printf("N.ro dei posti disponibili attualmente: %d\n",disp);

		int i=0;
		while(num_posti != 0){
		
			if(p[i].stato == LIBERO){
			
				p[i].stato = IN_AGGIORNAMENTO;

				sleep(1);

				printf("Il cliente %d, ha occupato il posto: %d\n", getpid(), i);

				p[i].stato = OCCUPATO;

				p[i].id_cliente = getpid();

				num_posti --;
			}else
				i++;
		}
	}else
		printf("NON ABBASTANZA POSTI DISPONIBI\n");
		

	vai(id_sem, ENTRO_IO);
}