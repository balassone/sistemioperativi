all: start main_client main_server

start: main.c
	gcc -o start  main.c

main_client: main_client.c header.h
	gcc -o main_client main_client.c

main_server: main_server.c header.h
	gcc -o main_server main_server.c

clean:
	rm -f start
	rm -f main_client
	rm -f main_server