#ifndef _HEADER_H_
#define _HEADER_H_

#define NUM_VOLTE 3
#define SYNCH 0		//per avvisare lett e scrittori
#define MUTEXS 1	//per prendere il buffer
#define MUTEXL 2	//per prendere il buffer
#define MUTEX  3	//per non scrivere tutti assieme

/*
sem per variabili conteggio lett	MUTEXL
sem per variabili conteggio scri	MUTEXS

mutua esclusione scrittori 	SYNCH
mutua esclisione lettori 	MUTEX
*/

typedef long msg;

            
typedef struct {
 	  	 int numlettori;
 	  	 int numscrittori;
 	  	 msg messaggio;
} Buffer;



void InizioLettura (int, Buffer*);
void FineLettura(int, Buffer*);
void InizioScrittura(int, Buffer*);
void FineScrittura(int, Buffer*);
void Lettore(int, Buffer*);
void Scrittore(int, Buffer*);

#endif //_HEADER_H_
