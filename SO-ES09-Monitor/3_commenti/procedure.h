#ifndef HEADER_H
#define HEADER_H

#include "monitor_signal_continue.h"

#define DIM 5

//aiuto a capire lo stato non sono semafori
#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2


//questa struttura possiamo metterla nella heap o nello stack del padre per poi passarla ai figli che la ereditano
struct ProdCons {
	int buffer[DIM];
	int stato[DIM];

	int numero_occupati;	//il mutex va messo qui (nella pthread?)
	int numero_liberi;

	Monitor m;	//variabile statica che protegge le altre
};

#define VARCOND_PRODUTTORI 0		//abbiamo usato 3 semafori invece di 4 (per implemetare varcond servono + semafori)
#define VARCOND_CONSUMATORI 1

void Produci(struct ProdCons * pc, int valore); //riferimento a prodcons e valore da produrre
int Consuma(struct ProdCons * pc); 				//restituisce consumo

#endif
