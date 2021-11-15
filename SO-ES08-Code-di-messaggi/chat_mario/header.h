#ifndef __HEADER__
#define __HEADER__

// Path per la FTOK
#define FTOK_PATH "."

// Tipo per il messaggio
#define TYPE 1		//deve essere un intero qualsiasi MA NON ZERO (che è usato da msg recieve), con n>0 viene letto prima il messaggio con lo stesso tipo

// Struct raltiva ai messaggi
struct mesg {
	long msgType;		// tipo messaggio-----------------------------------//il kernel si aspetta un long
	char message[20];	// messaggio effettivo								//va messo per primo perché la dimensione viene calcolata come 
};																			// (tutto-long), quindi se non è il primo viene tolta parte del messaggio

void Sender(int, int);
void Receiver(int);

#endif // __HEADER__