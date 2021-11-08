//concatenazione 2 vettori

#include <stdio.h>

//leggi
void leggi(int v[], const int n){

    int i;

    printf("sto leggendo");

    for(i=0;i<n;i++){
        printf("inserire elemento n. %d", i);
        scanf("%d",&v[i]);
    }
}

//stampa
void stampa(const int a[], const int n){

    int i;

    printf("stampa vettore:");
    for(i=0;i<n;i++){
        printf("elemento n. %d", a[i]);
    }    
}

//concatenazione vettore
void concatenazione( const int a[], const int b[], int c[], const int n){
    int i;

    printf("vettore concatenato");

	for (i=0;i<n;i++) 
		c[i]=a[i];
		c[n+i]=b[i];
}