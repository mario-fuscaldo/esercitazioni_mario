#ifndef PROCEDURE_H_
#define PROCEDURE_H_

//path & id for the ftok key for variable
#define PATH "./"
#define CHAR 'a'

//path & id for the ftok key for array
#define FPATH_VETT "./"
#define FCHAR_VETT 'c'

//semafori
#define MUTEX 0
#define SEM_NUM_POSTI 1

//variabili
#define LIBERO 0
#define OCCUPATO 1
#define IN_AGGIORNAMENTO 2

#define MAX_POSTI 80
#define N_CLIENTI 50
#define N_VISUALIZZATORI 1

/*
al contrario del vettore di stato classico qui non abbiamo una
struct al cui interno vengono conservati i vettori di buffer e stato
ma abbiamo un vettore al cui interno viene conservata
la struct con buffer e stato
*/

typedef struct{

	unsigned int id_cliente;
	unsigned int stato;
	
}posto;

#define CLIENTI 50
#define VISUALIZZATORE 1

/*
non abbiamo più la struttura e il riferimento del semaforo
ma abbiamo il vettore e il riferimento del semaforo*/

void visualizzatore(posto* vett, int sem_id);
void cliente(posto* vett, int sem_id, int* posti_disp);

#endif