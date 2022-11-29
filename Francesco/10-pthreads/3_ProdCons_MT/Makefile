FLAGS=-std=c++11 -Wall -pedantic -Wextra -pthread -g
OBJ=procedure.o main.o
DEPS=header.h

%.o: %.cpp ${DEPS}
	g++ -c -o $@ $< ${FLAGS}
main: ${OBJ}
	g++ -o $@ $^ ${FLAGS}
clean:
	rm -rf *.o
	rm -rf main
