all: eseguimi

eseguimi: main.o procedure.o semafori.o
	gcc -o eseguimi main.o procedure.o semafori.o

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o
	rm -f ./main