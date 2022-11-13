FLAGS=-std=c++11 -Wall -pedantic -Wextra
shmem_int: shmem_int.o
	g++ -o shmem_int shmem_int.o $(FLAGS)
shmem_int.o: shmem_int.cpp
	g++ -c shmem_int.cpp $(FLAGS)
clean:
	rm -rf *.o
	rm -rf shmem_int
