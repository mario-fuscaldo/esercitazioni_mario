#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>



struct monitor {

	int molo;
	int id_nave;

	//Aggiungere variabili per la sincronizzazione
    int num_lettori;
    int occupato;
    
    int coda_lettori;
    int coda_scrittori;
    
    pthread_mutex_t mutex;
    pthread_cond_t ok_aggiorna;
    pthread_cond_t ok_leggi;
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_molo(struct monitor * m, int molo);
int leggi_molo(struct monitor * m);



#endif
