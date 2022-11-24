DEPS=monitor_signal_continue.h procedure.h
OBJ=main.o monitor_signal_continue.o procedure.o
FLAGS=-std=c++11 -Wall -pedantic -Wextra -g

%.o: %.cpp ${FLAGS}
	g++ -c -o $@ $< ${FLAGS}
main: ${OBJ}
	g++ -o $@ $^ ${FLAGS}

clean:
	rm -rf *.o
	rm -rf main
