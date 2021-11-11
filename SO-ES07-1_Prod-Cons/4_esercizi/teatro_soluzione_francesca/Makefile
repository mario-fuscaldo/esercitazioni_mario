all: main.o visualizzatore.o processi.o semafori.o
	gcc -o main main.o processi.o semafori.o
	gcc -o visualizzatore visualizzatore.o processi.o semafori.o

main: main.o processi.o semafori.o
	gcc -o main main.o processi.o semafori.o

visualizzatore: visualizzatore.o processi.o semafori.o
	gcc -o visualizzatore visualizzatore.o processi.o semafori.o

main.o: main.c 
	gcc -c main.c

visualizzatore.o: visualizzatore.c
	gcc -c visualizzatore.c

processi.o: processi.c processi.h
	gcc -c processi.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o
	rm -f ./main
