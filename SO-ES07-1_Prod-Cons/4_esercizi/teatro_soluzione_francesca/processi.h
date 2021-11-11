#ifndef PROCESSI_H_
#define PROCESSI_H_

#define MUTEX 0	//mutua esclusione clienti	(non farli andare sulla stessa cosa)
#define SEMC 1	//cooperazione clienti		(solo uno modifica vettore di stato)
#define SEMV 2	//cooperazione visualizzatore-clienti

#define PATH "./"
#define CHAR 'a'

#define LIBERO 0
#define OCCUPATO 1
#define IN_AGGIORNAMENTO 2
#define DIM 80


typedef struct{

	unsigned int id_cliente;
	unsigned int stato;
	int disp;

}posto;

#define CLIENTI 50
#define VISUALIZZATORE 1


void clienti(posto *vet, int id_sem);
void visualizzatore(posto *vet, int id_sem);


#endif
