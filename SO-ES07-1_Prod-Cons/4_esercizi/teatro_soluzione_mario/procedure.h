#ifndef PROCEDURE_H_
#define PROCEDURE_H_

#define ENTRO_IO 0

#define PATH "./"
#define CHAR 'a'

#define LIBERO 0
#define OCCUPATO 1
#define IN_AGGIORNAMENTO 2
#define DIM 80

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

void presaDelPosto(posto [], int);
void visualizzazione(posto[]);

#endif