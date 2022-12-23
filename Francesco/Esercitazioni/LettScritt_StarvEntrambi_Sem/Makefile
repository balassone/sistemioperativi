C=g++
FLAGS=-std=c++11 -Wall -pedantic -Wextra -g
DEPS=semafori.h header.h
OBJ= main.o procedure.o semafori.o

%.o: %.cpp ${DEPS}
	${C} -c -o $@ $< ${FLAGS}
start: ${OBJ}
	${C} -o $@ $^ ${FLAGS}

clean:
	rm -rf *.o
	rm -rf start
