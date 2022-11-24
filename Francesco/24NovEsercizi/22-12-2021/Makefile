DEPS=header.h monitor_hoare.h
OBJ=main.o procedure.o monitor_hoare.o
FLAGS= -std=c++11 -Wall -pedantic -Wextra


%.o: %.cpp ${DEPS}
	g++ -c -o $@ $< ${FLAGS}
main: ${OBJ}
	g++ -o $@ $^ ${FLAGS}


clean:
	rm -rf *.o
	rm -rf main
