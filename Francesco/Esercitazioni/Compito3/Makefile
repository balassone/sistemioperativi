C=g++
FLAGS=-std=c++11 -Wall -pedantic -Wextra -pthread -g
DEPS=header.h
OBJ= main.o procedure.o

%.o: %.cpp ${DEPS}
	${C} -c -o $@ $< ${FLAGS}
start: ${OBJ}
	${C} -o $@ $^ ${FLAGS}

clean:
	rm -rf *.o
	rm -rf start
