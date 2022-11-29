FLAGS=-std=c++11 -Wall -pedantic -Wextra
DEPS=monitor_hoare.h procedure.h
OBJ=monitor_hoare.o procedure.o main.o

%.o: %.cpp ${DEPS}
	g++ -c -o $@ $< ${FLAGS}
driver: ${OBJ}
	g++ -o $@ $^ ${FLAGS}

clean:
	rm -rf *.o
	rm -rf driver
