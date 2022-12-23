
all:  start

start:  produttore consumatore
	gcc -g -o start start.c

produttore:
	gcc -o produttore produttore.c procedure.c -lm    

consumatore:
	gcc -g -o consumatore consumatore.c procedure.c -lm

clean:
	rm -f *.o 
	rm -f ./start ./produttore ./consumatore

