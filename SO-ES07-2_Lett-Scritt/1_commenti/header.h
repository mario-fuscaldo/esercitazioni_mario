		/*-------HEADER FILE-------------*/

#define MUTEXL 0
#define SYNCH 1
#define NUM_VOLTE 6


typedef long  msg;

typedef struct {

        int numlettori;
        msg messaggio;
    
} Buffer;


void Lettore(int,Buffer*);      //desctiore semaforo e puntatore a buffer in ingresso
void Scrittore(int,Buffer*);
