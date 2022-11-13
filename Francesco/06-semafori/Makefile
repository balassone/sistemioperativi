FLAGS=-std=c++11 -Wall -pedantic -Wextra
DEPS=semafori.h
OBJ=semafori.o main.o

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(FLAGS)
main: $(OBJ)
	g++ -o $@ $^ $(FLAGS)

clean:
	rm -rf main.o main
