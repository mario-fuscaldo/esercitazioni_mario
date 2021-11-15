#include "procedure.h"

#include <unistd.h>
#include <stdio.h>

void Produci(struct ProdCons * pc, int valore) {	//senza asterisco sarebbe la variabile statica
	//con i semafori si fa wait spazio disponibile
	//1. qui entramo nel monitor (ovvero chiamiamo il mutex)
	enter_monitor( &(pc->m) ); //vogliamo il riferimento di m quindi & (m prso con il punto) -> potresti fare una macro

	printf("Ingresso monitor - produzione\n");

	//2. controllo che ci sia posto sennò chiamo la wait condition
	while( pc->numero_liberi == 0 ) {	//NON USARE IF SERVE UNA COSA CHE CERCA SEMPRE SENNO' POTREBBE INVALIDARE IL CONTO
										//se è una sign e cont chi segnala poi si prende i liberi
		printf("Sospensione - produzione\n");
		wait_condition( &(pc->m), VARCOND_PRODUTTORI );
		printf("Riattivazione - produzione\n");
	}

	//3. check vettore di stato
	int i = 0;
	while( i<DIM && pc->stato[i] != LIBERO ) {
		i++;
	}

	//4. aggiorn vett di stato in unso
	pc->stato[i] = IN_USO;
	pc->numero_liberi--;

	leave_monitor( &(pc->m) );

	//CONSUMAZIONE E PRODUZIONE FUORI DAL MONITOR
	// ...operazione lenta...
	sleep(2);

	pc->buffer[i] = valore;

	printf("Produzione - posizione %d, valore %d\n", i, valore);

	//5. alla fine della produzione entro nel monitor
	enter_monitor( &(pc->m) );

	//6. aggiorno a occupato
	pc->stato[i] = OCCUPATO;
	pc->numero_occupati++;

	//7. avviso i consumatori
	signal_condition( &(pc->m), VARCOND_CONSUMATORI );

	//8. esco dal monitor
	leave_monitor( &(pc->m) );

	printf("Uscita monitor - produzione\n");
}

int Consuma(struct ProdCons * pc) {

	int valore;

	enter_monitor( &(pc->m) );

	printf("Ingresso monitor - consumazione\n");

	while( pc->numero_occupati == 0 ) {

		printf("Sospensione - consumazione\n");
		wait_condition( &(pc->m), VARCOND_CONSUMATORI );
		printf("Riattivazione - consumazione\n");
	}



	int i = 0;
	while( i<DIM && pc->stato[i] != OCCUPATO ) {
		i++;
	}


	pc->stato[i] = IN_USO;
	pc->numero_occupati--;

	leave_monitor( &(pc->m) );


	// ...operazione lenta...
	sleep(2);

	valore = pc->buffer[i];

	printf("Consumazione - posizione %d, valore %d\n", i, valore);


	enter_monitor( &(pc->m) );

	pc->stato[i] = LIBERO;
	pc->numero_liberi++;

	signal_condition( &(pc->m), VARCOND_PRODUTTORI );

	leave_monitor( &(pc->m) );

	printf("Uscita monitor - consumazione\n");

	return valore;

}

