FLAGS=-std=c++11 -Wall -pedantic -Wextra
OBJ=main.o monitor_signal_continue.o procedure.o
DEPS=procedure.h monitor_signal_continue.h

%.o: %.cpp ${DEPS}
	g++ -c -o $@ $< ${FLAGS}
driver: ${OBJ}
	g++ -o  $@ $^ ${DEPS}

clean:
	rm -rf *.o
	rm -rf driver
