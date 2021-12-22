		/*-------HEADER FILE-------------*/

#define MUTEXL 0        //serve a non far umentare il numero di lettori a caso
#define SYNCH 1         //cooperazione
#define NUM_VOLTE 6


typedef long  msg;

typedef struct {

        int numlettori;
        msg messaggio;
    
} Buffer;


void Lettore(int,Buffer*);      //desctiore semaforo e puntatore a buffer in ingresso
void Scrittore(int,Buffer*);
