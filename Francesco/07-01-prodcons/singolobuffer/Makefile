C=g++
FLAGS=-std=c++11 -Wall -pedantic -Wextra
OBJ=semafori.o procedure.o main.o
DEPS=semafori.h procedure.h

%.o: %.cpp $(DEPS)
	$(C) -c -o $@ $< $(FLAGS)
main: $(OBJ)
	$(C) -o $@ $^ $(FLAGS)
clean:
	rm -rf *.o
	rm -rf main
