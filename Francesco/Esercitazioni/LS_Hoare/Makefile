C=g++
FLAGS=-std=c++11 -Wall -pedantic -Wextra -g
DEPS=header.h monitor_hoare.h
OBJ=main.o monitor_hoare.o procedure.o

%.o: %.cpp ${DEPS}
	${C} -c -o $@ $< ${FLAGS}
start: ${OBJ}
	${C} -o $@ $^ ${FLAGS}

clean:
	rm -rf *.o
	rm -rf start
