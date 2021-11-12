#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "semafori.h"
#include "procedure.h"

int main(){
//-----------GESTIONE POSTI-----------

    //chiave per posti
    key_t chiave_posti = ftok(PATH, CHAR);

    if(chiave_posti<0){
        perror("errore chiave posti\n");
        exit(1);
    }

    //descrittore per posti
    int ds_posti = shmget(chiave_posti, sizeof(int), IPC_CREAT | 0664);
    if(ds_posti < 0){
        perror("ERR shmget num posti\n");
        exit(1);
    }

    //memory attach per posti
    int* num_posti  = (int*)shmat(ds_posti, NULL, 0);
    *num_posti  = MAX_POSTI;   

//---------GESTIONE ARRAY------------   
    
    //chiave per array
    key_t chiaveVettore = ftok(FPATH_VETT, FCHAR_VETT);
    
    if(chiaveVettore < 0 ){
        perror("ERR chiave vettore\n");
        exit(1);
    }

    //descrittore per array
    int ds_vet = shmget(chiaveVettore, MAX_POSTI*sizeof(posto), IPC_CREAT | 0664);
    if(ds_vet < 0){
        perror("ERR shmget vettore\n");
        exit(1);
    }

    //memory attach per array
    posto* vett = (posto*) shmat(ds_vet, NULL, 0);
    if(vett == (void*)-1){
        perror("err shmat\n");
        exit(1);
    } 


//-----------SEMAFORI----------------

    //creazione SEMAFORI
    key_t chiave_sem = ftok(PATH, CHAR);
    int sem_id = semget(chiave_sem, 2, IPC_CREAT | 0664);
    if(sem_id < 0){
        perror("errore semget\n");
        exit(1);
    }

    //settaggio dei semafori
    semctl(sem_id, MUTEX, SETVAL, 1);
    semctl(sem_id, SEM_NUM_POSTI, SETVAL, 1);

//-------------------------------------

    //INIT del vettore
    int i;
    for(i=0; i<MAX_POSTI; i++){
        vett[i].id_cliente = 0;
        vett[i].stato = LIBERO;
    }

    //avvio visualizzatore
    int pid=fork();
    if (pid==0){
    execl("./visualizzatore","./visualizzatore",NULL);
    exit(0);
    }

    //creazione clienti
    for(i = 0; i< N_CLIENTI; i++){
        int pid = fork();
        if(pid == 0){
            cliente(vett, sem_id, num_posti);
            exit(0);
        }
    }

    for(i = 0; i< N_CLIENTI + N_VISUALIZZATORI; i++){
        wait(NULL);
    }


    //dealloco shm del vettore
    shmctl(ds_vet, IPC_RMID, 0);

    //dealloco i semafori
    semctl(sem_id,MUTEX,IPC_RMID,NULL);
    semctl(sem_id,SEM_NUM_POSTI,IPC_RMID,NULL);

    return 0;
}