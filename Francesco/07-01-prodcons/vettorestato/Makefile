FLAGS=-std=c++11 -Wall -pedantic -Wextra
DEPS=procedure.h semafori.h
OBJ=main.o procedure.o semafori.o

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(FLAGS)
main: $(OBJ)
	g++ -o $@ $^ $(FLAGS)
clean:
	rm -rf *.o
	rm -rf main
