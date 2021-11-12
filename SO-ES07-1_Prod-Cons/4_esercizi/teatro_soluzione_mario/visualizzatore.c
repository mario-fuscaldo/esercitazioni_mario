#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "procedure.h"
#include "semafori.h"

int main(){

    //assegnazione chiavi
    key_t chiave_vett = ftok(FPATH_VETT, FCHAR_VETT);

    key_t chiave_sem = ftok(PATH, CHAR);
        //perché questa?


    //descrittori
    int ds_vet = shmget(chiave_vett, (MAX_POSTI) * sizeof(posto), IPC_CREAT | 0664);
    if(ds_vet < 0){
        perror("err shmget chiave_ vett VISUALIZZATORE\n");
        exit(1);
    }


    int ds_sem = semget(chiave_sem, 1, IPC_CREAT | 0664);
    if(ds_sem < 0){
        perror("errore semget chiave_sem VISUALIZZATORE \n");
        exit(1);
    } 
    //perché questa?

    //smh attach    
    posto* vett = (posto*) shmat(ds_vet, NULL, 0);
    if(vett == (void*) -1){
        perror("errore shmat VISUALIZZATORE \n");
        exit(1);
    }

    //chiamo visualizzatore
    visualizzatore(vett, ds_sem);
    

    //dealloco shm del vettore
    shmctl(ds_vet, IPC_RMID, 0);

    //dealloco i semafori
    semctl(ds_sem,MUTEX,IPC_RMID,NULL);
    return 0;
}