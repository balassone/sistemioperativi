FLAGS=-std=c++11 -Wall -pedantic -Wextra
OBJ=monitor_signal_continue.o procedure.o main.o
DEPS=monitor_signal_continue.h procedure.h

%.o: %.cpp ${DEPS}
	g++ -c -o $@ $< ${FLAGS}
eseguibile: ${OBJ}
	g++ -o $@ $^ ${FLAGS}

clean:
	rm -rf *.o
	rm -rf eseguibile
